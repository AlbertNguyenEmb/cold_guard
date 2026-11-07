# Kiểm tra GPIO

Trạng thái: chưa chạy trên phần cứng; cần triển khai BSP và door driver trước.

- [ ] Đối chiếu GPIO trong `app_config.h` với sơ đồ board và mức điện áp thiết bị.
- [ ] GPIO chưa gán (`-1`) bị từ chối trước khi gọi API GPIO.
- [ ] Boot/reset giữ output cảnh báo ở mức an toàn đã chọn cho mạch.
- [ ] Đóng/mở cửa cập nhật đúng trạng thái và cờ `door_valid`.
- [ ] Tín hiệu rung tiếp điểm được debounce, không tạo nhiều sự kiện giả.
- [ ] Tháo dây hoặc lỗi input được xử lý theo thiết kế phần cứng.

Ghi lại board, wiring, firmware, bước thực hiện, kỳ vọng, kết quả và log.
