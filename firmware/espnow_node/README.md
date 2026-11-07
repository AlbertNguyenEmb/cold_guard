# ESP-NOW sensor node

Project ESP-IDF độc lập cho DS18B20, target mặc định **`esp32` (ESP32 thường)**.
Controller dùng **`esp32s3`** riêng, không ảnh hưởng target của node.

Nếu còn `sdkconfig`/cache ESP32-S3 từ cấu hình cũ, tại `firmware/` chạy một lần:

```powershell
.\build.cmd espnow_node -Target esp32
```

Lệnh này tạo lại cấu hình cho ESP32 rồi build; các lần sau chỉ cần build bình thường.

Trong PowerShell thường tại thư mục này:

```powershell
.\build.cmd
```

File `build.cmd` tại node tự chọn project này. Cũng hỗ trợ
`.\build.cmd espnow_node -Target esp32` khi cần chọn lại chip.

Để dùng trực tiếp lệnh build/flash trong cùng terminal, nạp môi trường một lần:

```powershell
. ..\export.ps1
idf.py build
idf.py -p COM6 flash monitor
```
idf.py -C espnow_node -p COM6 flash

Thay COM6 bằng cổng node thực tế. Nếu terminal đã kích hoạt ESP-IDF sẵn,
bỏ qua dòng nạp `export.ps1`.

Từ thư mục `firmware/`, dùng `idf.py -C espnow_node build`.

## Điền code

- `main/app_config.h`: chân DS18B20, node ID, chu kỳ lấy mẫu, channel, MAC controller.
  GPIO `-1` và MAC toàn 0 hiện là placeholder.
- `main/ds18b20_driver.c`: 1-Wire, tìm thiết bị, chuyển đổi nhiệt độ, CRC và lỗi.
- `main/espnow_sender.c`: NVS, netif, event loop, Wi-Fi STA, channel, ESP-NOW,
  peer và callback gửi bất đồng bộ.
- `main/main.c`: đọc nhiệt độ định kỳ, tạo packet rồi gọi sender khi đọc thành công.

Hiện driver đọc và sender đều trả `ESP_ERR_NOT_SUPPORTED`; khung chưa phát gói tin.
Các hàm init chỉ log `TODO`. Trước khi triển khai phép đổi nhiệt độ sang số nguyên,
cần kiểm tra giá trị hữu hạn và nằm trong dải đo của cảm biến.

## Giao thức dùng chung

`main/espnow_protocol.h` include `../common/espnow_protocol_shared.h` qua include
path CMake. Bố cục gói sensor version 1 dài 16 byte, các số nguyên little-endian:

| Byte | Nội dung |
| --- | --- |
| 0 | version, uint8 |
| 1 | message_type, uint8 |
| 2–3 | node_id, uint16 |
| 4–7 | sequence, uint32 |
| 8–11 | temperature_millicelsius, int32 |
| 12–15 | flags, uint32; bit 0 đánh dấu nhiệt độ hợp lệ |

Sender/receiver cần serialize/deserialize và kiểm tra length/version rõ ràng;
chưa có phần encode/decode wire trong khung. Hai board phải dùng cùng channel.
Build độc lập nhưng vẫn cần giữ thư mục `common/` cạnh hai project.
Xem [README chung](../README.md) về thêm thư viện 1-Wire/DS18B20 nếu cần.
