# Cold Guard firmware

Khung gồm **hai project ESP-IDF độc lập**, mỗi project tạo một firmware riêng:

- `main_controller/`: bộ điều khiển trung tâm, cảm biến Modbus/cửa, nhận ESP-NOW,
  Wi-Fi, MQTT, cảnh báo và HTTP.
- `espnow_node/`: node DS18B20 gửi dữ liệu qua ESP-NOW.
- `common/espnow_protocol_shared.h`: định nghĩa gói tin dùng chung. Hai file
  `espnow_protocol.h` trong từng project include file này để tránh lệch giao thức.
- `tests/`: quy trình kiểm tra thủ công sau khi bổ sung phần cứng và logic.

Hai board được cấu hình riêng: **main_controller → ESP32-S3 (`esp32s3`)**,
**espnow_node → ESP32 thường (`esp32`)**. Mỗi project có `sdkconfig.defaults`,
`sdkconfig` và thư mục `build/` riêng; không chọn một target chung cho `firmware/`.

Đã khai báo toàn bộ file `.c` trong CMake, thêm header công khai cho từng module
và nối luồng khởi động/task. Các hàm có `TODO` là chỗ để điền code.
Đây là **khung build được**, chưa phải firmware có đầy đủ chức năng phần cứng.
Các hàm khởi tạo stub chỉ log cảnh báo và trả `ESP_OK` để chạy khung; đọc cảm biến,
mã hóa telemetry, gửi MQTT/ESP-NOW và xử lý lệnh trả `ESP_ERR_NOT_SUPPORTED`.
Vì vậy khung chưa phát dữ liệu, chưa kết nối mạng và chưa kích GPIO.

## Build nhanh

Trong PowerShell thường tại thư mục `firmware/`, chạy:

```powershell
.\build.cmd
```

Lệnh này tự nạp môi trường ESP-IDF 6.1 đang cài trên máy và build cả hai project.
Để build riêng một project:

```powershell
.\build.cmd main_controller
.\build.cmd espnow_node
```

`build.cmd` gọi `tools/build.ps1` trong tiến trình PowerShell con, nên không cần
`idf.py` có sẵn trong terminal đang dùng và không đổi execution policy lưu trên máy.
Nếu chuyển sang máy khác, có thể chỉ định script kích hoạt của bản cài ESP-IDF:

```powershell
.\build.cmd -ActivationScript "C:\path\to\ESP-IDF-activation.ps1"
```

Script kích hoạt cần thiết lập cả `IDF_PATH` và `IDF_PYTHON_ENV_PATH`.

Nếu muốn dùng trực tiếp `idf.py`, cần **nạp ESP-IDF trước trong mỗi terminal mới**.
Với bản EIM đang có trên máy, chạy theo thứ tự:

```powershell
$env:PYTHONUTF8 = "1"
. C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1
idf.py -C main_controller build
idf.py -C espnow_node build
```

Đã có script nạp môi trường cho terminal hiện tại. Từ `firmware/`, cách ngắn hơn:

```powershell
. .\export.ps1
idf.py -C main_controller build
idf.py -C espnow_node build
```

Dấu chấm đầu tiên và khoảng trắng trong `. .\export.ps1` là cú pháp nạp script
vào PowerShell hiện tại. Chạy một lần cho mỗi terminal mới. `build.cmd` tự kích
hoạt môi trường trong tiến trình con nên sau khi build xong, terminal cha vẫn
chưa có lệnh `idf.py` nếu chưa nạp `export.ps1`.

Nếu terminal đang ở `main_controller/` hoặc `espnow_node/`, chạy `.\build.cmd`
để build chính project đó; các file build cục bộ cũng nhận tên project và
`-Target` như script ở thư mục cha. Để dùng `idf.py` tại thư mục con, nạp
`. ..\export.ps1` rồi chạy `idf.py build`, `idf.py flash`, ...

Hoặc mở **ESP-IDF Terminal** từ extension ESP-IDF trong VS Code.

Để đổi target và build một project ngay từ PowerShell thường:

```powershell
.\build.cmd main_controller -Target esp32s3
.\build.cmd espnow_node -Target esp32
```

Hoặc dùng trực tiếp trong ESP-IDF terminal đã kích hoạt:

```powershell
idf.py -C main_controller set-target esp32s3
idf.py -C espnow_node set-target esp32
idf.py -C main_controller build
idf.py -C espnow_node build
```

`set-target` tạo lại cấu hình và build của project đã chọn; chỉ cần chạy khi đổi
chip. Sau khi sửa nội dung các file có sẵn, chỉ chạy lại `build`.
Nếu thêm file `.c` mới, bổ sung đường dẫn vào `main/CMakeLists.txt` tương ứng.
Không chạy CMake từ thư mục `main/`; đây là component, không phải project độc lập.

## Chọn project/target trong VS Code

Mở **File → Open Workspace from File… → `cold_guard.code-workspace`**.
Sau đó nhấn `F1` → **ESP-IDF: Pick a Workspace Folder**, chọn `main_controller`
hoặc `espnow_node` trước khi Build, Set Target, Flash hay Monitor. Target của
controller là `esp32s3`, target của node là `esp32`. Chọn cổng COM riêng khi flash.
Cấu hình từng folder đã đặt `PYTHONUTF8=1` cho công cụ ESP-IDF.

Nếu chỉ mở folder `firmware/`, extension sẽ xem chính folder đó là project và báo
`CMakeLists.txt not found in project directory .../firmware` khi Set Target.
`cmake.sourceDirectory` chỉ cấu hình extension CMake Tools, không chọn project
cho extension ESP-IDF. Có thể mở riêng `main_controller/` hoặc `espnow_node/`
thay vì dùng workspace hai project.

Tham khảo: [ESP-IDF: nhiều project trong VS Code](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/additionalfeatures/multiple-projects.html).

## Flash và xem log

Tại `firmware/`, nạp môi trường rồi thay `COM5`/`COM6` bằng cổng thực tế:

```powershell
. .\export.ps1
idf.py -C main_controller -p COM5 flash monitor
idf.py -C espnow_node -p COM6 flash monitor
```

Chỉ chạy dòng flash cho board/cổng muốn nạp. Tại `firmware/` phải có
`-C main_controller` hoặc `-C espnow_node`; thư mục cha không phải một project
ESP-IDF. Nếu đang ở thư mục project con, có thể dùng `idf.py -p COM5 flash`
sau khi nạp môi trường, không cần `-C`.

Thoát monitor bằng `Ctrl+]`. Khi chạy bản khung, log mong đợi có cảnh báo `TODO`
và dòng `scaffold ready`. Chưa kiểm tra flash hay hoạt động trên board thực tế.

## Điền code ở đâu?

| Phần việc | Vị trí |
| --- | --- |
| Chân GPIO, UART, Wi-Fi, MQTT, chu kỳ task | `main_controller/main/app_config.h` |
| GPIO và mức output ban đầu | `main_controller/main/bsp/` |
| UART/RS485, thanh ghi Modbus, cảm biến cửa | `main_controller/main/drivers/` |
| Wi-Fi, nhận ESP-NOW, MQTT | `main_controller/main/communication/` |
| Dữ liệu chung, task, telemetry, FSM, lệnh | `main_controller/main/application/` |
| HTTP endpoints | `main_controller/main/web/` |
| Chân DS18B20, node ID, channel, MAC trung tâm | `espnow_node/main/app_config.h` |
| Driver DS18B20 và gửi ESP-NOW | `espnow_node/main/` |
| Phiên bản và định dạng gói tin | `common/espnow_protocol_shared.h` |

Chân GPIO mặc định là `-1` (chưa gán). Cần điền theo sơ đồ mạch trước khi viết
code cấu hình GPIO. Luôn kiểm tra cờ validity trước khi dùng số đo; khi driver
chưa có hoặc đọc lỗi, giá trị 0 trong vùng nhớ không phải số đo hợp lệ.

## Thư viện và CMake

Các dependency có sẵn trong ESP-IDF cho GPIO, UART, Wi-Fi, NVS, FreeRTOS, timer
và HTTP đã được khai báo. Khung không cần tải thư viện bên ngoài để build.

Khi triển khai MQTT trên ESP-IDF 6.x, thêm ESP-MQTT từ Component Registry:

```powershell
idf.py -C main_controller add-dependency "espressif/mqtt"
```

Sau đó bổ sung `espressif__mqtt` vào `PRIV_REQUIRES` của
`main_controller/main/CMakeLists.txt`. Nếu chọn thư viện Modbus hoặc
1-Wire/DS18B20 bên ngoài, cũng thêm dependency và tên component tương ứng khi
triển khai driver. Các thư viện này chưa được cài tự động vì chưa chọn cách
triển khai và chưa cần cho khung hiện tại. Nên lưu `idf_component.yml` và
`dependencies.lock` vào Git khi bắt đầu dùng managed components.

## Kết quả kiểm tra khung

Ngày 07/11/2026: cả hai project build thành công bằng ESP-IDF 6.1.0, controller
cho **ESP32-S3** và node cho **ESP32 thường**, tạo
`main_controller/build/cold_guard_main_controller.bin` và
`espnow_node/build/cold_guard_espnow_node.bin`. Chưa flash/test trên board.
Xem [checklist tích hợp](tests/integration_test.md) để tiếp tục kiểm tra chức năng.

Cache build cũ của controller trỏ tới đường dẫn project trước khi di chuyển đã
được giữ tại `main_controller/build_previous_layout/`; build hiện tại dùng `build/`.

## Cấu hình SDK

Theo cơ chế ESP-IDF, `sdkconfig.defaults` cung cấp giá trị mặc định; giá trị đã có
trong `sdkconfig` được ưu tiên. Dùng `idf.py -C <project> menuconfig` để chỉnh cấu
hình đang dùng. Không chỉnh file sinh tự động trong `build/`.

Tham khảo chính thức:
[ESP-IDF build system](https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-guides/build-system.html),
[ESP-MQTT](https://github.com/espressif/esp-mqtt).
