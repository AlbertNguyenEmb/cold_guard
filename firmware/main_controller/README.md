# Main controller

Project ESP-IDF cho bộ điều khiển Cold Guard, target mặc định `esp32s3`.
Trong PowerShell thường tại thư mục này, chạy:

```powershell
.\build.cmd
```

Lệnh tự kích hoạt môi trường ESP-IDF đang cài trong tiến trình build riêng.
Để dùng trực tiếp `idf.py` trong terminal hiện tại, chạy `. ..\export.ps1`
một lần trước. Nếu dùng ESP-IDF terminal đã kích hoạt sẵn, có thể chạy trực tiếp:

```powershell
idf.py build
idf.py -p COM5 flash monitor
```
idf.py -C main_controller -p COM5 flash

Từ thư mục `firmware/`, dùng `idf.py -C main_controller build`.

## Luồng khởi động

`main/main.c` khởi tạo state → BSP → driver → Wi-Fi → ESP-NOW → MQTT → alarm FSM
→ command handler → web server → sensor task và telemetry task.

- `sensor_task`: đọc Modbus và cửa, cập nhật dữ liệu/cờ validity qua API state,
  rồi gọi FSM. Stub đọc cảm biến trả lỗi nên state ban đầu không hợp lệ.
- `telemetry_task`: lấy snapshot, gọi encoder, rồi publish khi encoder thành công.
  Encoder hiện trả `ESP_ERR_NOT_SUPPORTED` nên chưa gửi dữ liệu.
- `app_state`: các API đọc/ghi snapshot dùng critical section; không giữ khóa khi
  đọc UART, gọi mạng hoặc thực hiện thao tác chờ.
- `espnow_receiver`: TODO nhận, kiểm tra và chuyển gói tin vào queue để task xử lý.

## Triển khai tiếp

1. Điền GPIO/UART/Wi-Fi/MQTT trong `main/app_config.h`.
2. Viết BSP và driver trong `bsp/`, `drivers/`.
3. Viết kết nối Wi-Fi và sự kiện ready/reconnect. Khi triển khai mạng thật, chỉ
   khởi động ESP-NOW/MQTT/HTTP sau khi điều kiện mạng tương ứng đã sẵn sàng.
4. ESP-NOW RX callback chỉ kiểm tra nhanh và đẩy queue; không xử lý chặn trong callback.
   Wi-Fi STA và ESP-NOW phải phối hợp dùng cùng channel.
5. Bổ sung state cho từng node, timestamp và timeout; không ghi đè dữ liệu Modbus
   bằng dữ liệu node nếu chưa định nghĩa rõ nguồn đo.
6. Hoàn thiện telemetry, FSM, command handler và HTTP.

Toàn bộ `.c` trong cây đã được khai báo trong `main/CMakeLists.txt`. Các hàm init
stub trả `ESP_OK` để chạy được khung; thay bằng init thực và xử lý lỗi khi triển khai.
Các thao tác chưa thực hiện trả `ESP_ERR_NOT_SUPPORTED` hoặc không làm gì, có `TODO`.

Gói ESP-NOW được định nghĩa tại `../common/espnow_protocol_shared.h`; không tạo
bản sao định nghĩa riêng trong controller. Khi thay đổi wire format cần tăng version.
Xem [README chung](../README.md) về dependency MQTT trên IDF 6.x và quy trình build.
