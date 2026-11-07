param(
    [ValidateSet('all', 'main_controller', 'espnow_node')]
    [string]$Project = 'all',

    [ValidateSet('esp32', 'esp32s3')]
    [string]$Target,

    [string]$ActivationScript = 'C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1'
)

$ErrorActionPreference = 'Stop'
$env:PYTHONUTF8 = '1'
$firmwarePath = Split-Path -Parent $PSScriptRoot

try {
    if ($Target -and $Project -eq 'all') {
        throw 'Select one project when changing target, e.g. build.cmd espnow_node -Target esp32.'
    }

    if (-not (Test-Path -LiteralPath $ActivationScript -PathType Leaf)) {
        throw "ESP-IDF activation script not found: $ActivationScript. Pass -ActivationScript with the path from your ESP-IDF installation."
    }

    # Activate ESP-IDF inside this child PowerShell process. The calling
    # terminal does not need idf.py on PATH or an activated Python environment.
    . $ActivationScript

    if (-not $env:IDF_PATH -or -not $env:IDF_PYTHON_ENV_PATH) {
        throw 'The activation script did not configure IDF_PATH and IDF_PYTHON_ENV_PATH.'
    }

    $idfPython = Join-Path $env:IDF_PYTHON_ENV_PATH 'Scripts\python.exe'
    $idfEntryPoint = Join-Path $env:IDF_PATH 'tools\idf.py'
    if (-not (Test-Path -LiteralPath $idfPython -PathType Leaf) -or
        -not (Test-Path -LiteralPath $idfEntryPoint -PathType Leaf)) {
        throw 'The configured ESP-IDF Python interpreter or idf.py does not exist.'
    }

    # A terminal opened for one board may export IDF_TARGET. Let each project's
    # sdkconfig (or explicit set-target action) choose its own chip instead.
    Remove-Item Env:IDF_TARGET -ErrorAction SilentlyContinue

    $projects = if ($Project -eq 'all') {
        @('main_controller', 'espnow_node')
    } else {
        @($Project)
    }

    foreach ($projectName in $projects) {
        $projectPath = (Resolve-Path -LiteralPath (Join-Path $firmwarePath $projectName)).Path
        if ($Target) {
            # set-target runs fullclean. Verify its default build directory stays
            # inside this workspace, and reject a redirected build directory.
            $buildPath = [System.IO.Path]::GetFullPath((Join-Path $projectPath 'build'))
            if (-not $buildPath.StartsWith($firmwarePath + '\', [System.StringComparison]::OrdinalIgnoreCase)) {
                throw "Build directory is outside the firmware workspace: $buildPath"
            }
            if (Test-Path -LiteralPath $buildPath) {
                $buildItem = Get-Item -LiteralPath $buildPath
                if ($buildItem.Attributes -band [System.IO.FileAttributes]::ReparsePoint) {
                    throw "Refusing to clean a redirected build directory: $buildPath"
                }
            }
            Write-Host "Setting $projectName target to $Target (regenerates sdkconfig)..."
            & $idfPython $idfEntryPoint -C $projectPath set-target $Target
            if ($LASTEXITCODE -ne 0) {
                exit $LASTEXITCODE
            }
        }
        Write-Host "Building $projectName..."
        & $idfPython $idfEntryPoint -C $projectPath build
        if ($LASTEXITCODE -ne 0) {
            exit $LASTEXITCODE
        }
    }

    Write-Host 'Build completed successfully.'
    exit 0
} catch {
    [Console]::Error.WriteLine($_.Exception.Message)
    exit 1
}
