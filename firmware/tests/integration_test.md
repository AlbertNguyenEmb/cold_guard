# Kiểm tra tích hợp

Trạng thái: checklist chưa chạy trên board. Build thành công không đồng nghĩa
với các chức năng trong checklist đã được triển khai hoặc đạt yêu cầu.

## Build khung

Đã kiểm tra ngày **07/11/2026**, ESP-IDF **6.1.0**, target riêng từng board:

| Project | Target | Kết quả | File tạo ra |
| --- | --- | --- | --- |
| `main_controller` | `esp32s3` | PASS, build exit code 0 | `main_controller/build/cold_guard_main_controller.bin` |
| `espnow_node` | `esp32` | PASS, set-target và build exit code 0 | `espnow_node/build/cold_guard_espnow_node.bin` |

Đã đối chiếu CMake khai báo đủ 14 file C của controller và 3 file C của node.
Đã chạy `./build.cmd` từ PowerShell chưa kích hoạt ESP-IDF: script tự nạp môi
trường, build lần lượt cả hai project và kết thúc với exit code 0 cùng thông báo
`Build completed successfully.`
Sau khi tách target đã chạy `./build.cmd espnow_node -Target esp32` trong môi
trường có `IDF_TARGET=esp32s3`: node vẫn chọn đúng ESP32, build thành công.
Đã chạy `./build.cmd main_controller` với `IDF_TARGET=esp32`: controller vẫn build
đúng ESP32-S3. File metadata `build/project_description.json` xác nhận target riêng.
Đã kiểm tra `. ./export.ps1` trong PowerShell thường: `idf.py --version` trả
`ESP-IDF v6.1`. Đã chạy thành công file build cục bộ: `./build.cmd` tại
`main_controller/` và `./build.cmd espnow_node` tại `espnow_node/`, exit code 0.
Đây là kết quả biên dịch/liên kết; các bước boot và kiểm tra phần cứng bên dưới
chưa được thực hiện. SDK có cảnh báo CMake/Kconfig nội bộ nhưng không chặn build.

Tại thư mục `firmware/`, trong PowerShell thường:

```powershell
.\build.cmd
```

Hoặc trong ESP-IDF terminal đã kích hoạt:

```powershell
idf.py -C main_controller build
idf.py -C espnow_node build
```

Kỳ vọng: cả hai lệnh kết thúc thành công, tạo `.elf` và `.bin` riêng trong
`main_controller/build/` và `espnow_node/build/`. Chạy lại sau khi sửa một `.c`
để kiểm tra build tăng dần.

## Boot khung

- [ ] Flash từng board; log có `scaffold ready` và các cảnh báo `TODO`.
- [ ] Controller tạo sensor task và telemetry task, không reboot/watchdog.
- [ ] Không có số đo hợp lệ hay gói gửi khi các driver/encoder còn stub.

## Khi hoàn thiện chức năng

- [ ] Hoàn tất các checklist GPIO, Modbus, ESP-NOW và MQTT.
- [ ] Đường đi Modbus/cửa → state → FSM → telemetry → MQTT đúng nguồn dữ liệu.
- [ ] Đường đi DS18B20 → ESP-NOW → queue → state từng node → telemetry đúng node ID.
- [ ] FSM kiểm tra validity, ngưỡng, hysteresis và timeout theo đặc tả được chốt.
- [ ] Web status và MQTT đọc snapshot nhất quán khi sensor task đang cập nhật.
- [ ] Mất cảm biến/node/Wi-Fi/broker được phát hiện và phục hồi đúng thiết kế.
- [ ] Reboot hai board theo thứ tự khác nhau vẫn khôi phục hệ thống.
- [ ] Chạy liên tục theo thời lượng yêu cầu, theo dõi heap, stack và watchdog.

Mỗi lần kiểm tra ghi ngày, ID board, target/IDF, cấu hình, phiên bản firmware,
bước thực hiện, kỳ vọng, kết quả thực tế và log kèm theo.
