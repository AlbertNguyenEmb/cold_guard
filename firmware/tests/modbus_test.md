# Kiểm tra Modbus

Trạng thái: chưa chạy; cần hoàn thiện driver RS485/Modbus và bảng thanh ghi.

- [ ] Xác nhận slave ID, baud rate, parity, stop bits, function code và register map.
- [ ] Kiểm tra TX/RX/DE, dây A/B và cấu hình phần cứng theo thiết bị.
- [ ] Đọc nhiệt độ/độ ẩm, đối chiếu hiển thị thiết bị; kiểm tra scale và dấu.
- [ ] CRC lỗi, response thiếu hoặc sai slave ID bị từ chối.
- [ ] Mất cảm biến hoặc timeout đặt `sensor_valid=false`; không xuất số đo giả.
- [ ] Kết nối lại khôi phục dữ liệu hợp lệ; task không bị treo và không watchdog reset.

Lưu raw request/response, timestamp, kỳ vọng và kết quả.
