# Kiểm tra MQTT

Trạng thái: chưa chạy; cần thêm ESP-MQTT và hoàn thiện Wi-Fi/MQTT/telemetry/lệnh.

- [ ] Cấu hình broker, xác thực, topic, QoS và TLS nếu hệ thống yêu cầu.
- [ ] Chỉ tạo kết nối/publish sau khi các trạng thái mạng tương ứng sẵn sàng.
- [ ] Subscriber nhận telemetry đúng schema, đơn vị, node ID và timestamp.
- [ ] Số đo không hợp lệ được thể hiện null/absent hoặc bằng cờ validity rõ ràng.
- [ ] Payload quá dài trả lỗi, không tràn buffer và không publish JSON bị cắt.
- [ ] Command hợp lệ được xử lý; command sai schema/độ dài bị từ chối.
- [ ] Ngắt Wi-Fi/broker rồi bật lại: reconnect và subscribe lại đúng thiết kế.
- [ ] Publish thất bại/queue đầy không làm treo sensor task.

Lưu broker/version, topic, payload mẫu, log và kết quả; không đưa mật khẩu vào log.
