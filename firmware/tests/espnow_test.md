# Kiểm tra ESP-NOW

Trạng thái: chưa chạy; cần triển khai DS18B20, sender, receiver và wire codec.

- [ ] Cả hai project build; node ID, controller MAC và channel đã cấu hình đúng.
- [ ] Đọc DS18B20 thành công và giá trị hợp lệ trước khi gửi.
- [ ] Packet version 1 dài 16 byte, serialize/deserialize đúng little-endian.
- [ ] Controller nhận đúng node ID, sequence, nhiệt độ và cờ validity.
- [ ] Gói sai length, version hoặc message type bị loại, không đọc vượt buffer.
- [ ] RX callback chuyển việc xử lý sang queue; queue đầy được xử lý rõ ràng.
- [ ] Mất node gây stale/timeout; kết nối lại phục hồi theo thiết kế.
- [ ] Kiểm tra khi controller kết nối Wi-Fi AP và khi AP thay đổi channel.
- [ ] Tháo DS18B20 không tạo số đo hợp lệ giả hoặc gửi giá trị ngoài dải.

Lưu MAC/channel, log hai board, số gói nhận/mất và kết quả.
