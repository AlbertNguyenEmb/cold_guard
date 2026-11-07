param(
    [string]$ActivationScript = 'C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1'
)

# Dot-source this file: . .\export.ps1
# Unlike build.cmd, this activates ESP-IDF in the current terminal.
if (-not (Test-Path -LiteralPath $ActivationScript -PathType Leaf)) {
    throw "ESP-IDF activation script not found: $ActivationScript"
}

$env:PYTHONUTF8 = '1'
. $ActivationScript

# Each of the two projects selects its own chip from sdkconfig/defaults.
Remove-Item Env:IDF_TARGET -ErrorAction SilentlyContinue

if (-not (Get-Command idf.py -ErrorAction SilentlyContinue)) {
    throw 'ESP-IDF activation did not provide the idf.py command.'
}
Write-Host 'ESP-IDF ready in this terminal. From firmware, use idf.py -C main_controller or idf.py -C espnow_node followed by the action.'
