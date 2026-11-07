# ColdGuard Data Protocol v1.0

Giao thức thống nhất trong nhóm (Member 1, Member 2, Member 3).

## Files
- `coldguard_protocol_v1.json`: danh sách device/zone, topic, quy tắc, các mẫu payload, ánh xạ CoreIOT.
- `coldguard_examples_v1.json`: JSON mẫu theo từng loại bản tin.
- `coldguard_message_v1.schema.json`: JSON Schema để kiểm tra bản tin nội bộ.

## Data flow
1. ESP32 phụ đọc DS18B20 rồi gửi ESP-NOW -> Yolo UNO (binary packet; KHÔNG phải MQTT JSON).
2. Yolo UNO đóng gói zone_a (SHT40 Modbus) và zone_b (ESP-NOW) thành JSON theo giao thức này.
3. Yolo UNO publish MQTT LAN đến Mosquitto trên PC Gateway.
4. Gateway kiểm tra schema, chống trùng `(device_id, boot_id, seq, zone_id)`, lưu SQLite kèm `received_at` UTC.
5. Gateway biến đổi dữ liệu sang ThingsBoard/CoreIOT `v1/devices/me/telemetry` theo từng device tương ứng.
6. CoreIOT RuleChain xử lý alarm; RPC trở lại Gateway -> `coldguard/main/command` -> ESP32 -> `coldguard/main/ack` -> Gateway -> cloud response.
7. Node Tasmota xuất JSON chuẩn của Tasmota; Member 3 ánh xạ tên field vào CoreIOT (không thay giao thức gốc Tasmota).

## MQTT LAN topics
| Topic | Bên gửi | Bên nhận |
|---|---|---|
| `coldguard/zone_a/telemetry` | Yolo | Gateway |
| `coldguard/zone_b/telemetry` | Yolo relays ESP-NOW | Gateway |
| `coldguard/main/status` | Yolo (retained + LWT) | Gateway |
| `coldguard/main/command` | Gateway | Yolo |
| `coldguard/main/ack` | Yolo | Gateway |
| `coldguard/events` | Gateway | Local UI/event log |

Use MQTT QoS 1. **Never retain commands**; set LWT for main status. QoS 1 can duplicate messages: Gateway must deduplicate.

## Field rules
- JSON keys in `snake_case`; IDs lower-case/hyphen. No unit in numeric values.
- `temperature_c`: °C, `humidity_pct`: %RH. `null` means unavailable, `0` is a valid measurement.
- `door_open=true` = open. `sensor_ok=false` -> invalid temp/humidity must be `null`.
- Device timestamps `ts` are RFC3339 UTC strings or `null`; if `null`, Gateway attaches UTC reception time. Do not confuse MCU `uptime_ms` with UTC.
- `boot_id` changes on each device reboot. `seq` increments for each measurement (origin device). Store `(device_id, boot_id, seq, zone_id)` unique in SQLite.
- Command `request_id` is mandatory; ACK must return exactly the same ID. Muting buzzer does not clear an active alarm.
- `set_threshold` must validate `min_c < max_c` in firmware/Gateway (JSON Schema cannot check cross-field numeric comparison reliably here).
- Gateway should enforce stale-command timeout and validation of ranges; no replay of old commands after reconnection.

## Real-world vs sample
All numbers and timestamps in examples are **illustrative**. CoreIOT device tokens, Wi-Fi passwords, DB files and `.env` must not be committed.

## Example cloud adapter (Member 2 / Member 3)
Input internal zone_a sample:
```json
{"v":1,"type":"telemetry","device_id":"yolo-main-01","zone_id":"zone_a","boot_id":"a1b2c3d4","seq":17,"uptime_ms":17000,"ts":null,"data":{"temperature_c":5.8,"humidity_pct":75.4,"door_open":false,"sensor_ok":true,"source":"sht40_modbus"}}
```
Gateway sends to the CoreIOT device mapped to `COLD_ZONE_A` (using the appropriate credential/session):
```json
{"ts":1793800800000,"values":{"temperature_c":5.8,"humidity_pct":75.4,"door_open":false,"sensor_ok":true}}
```
`ts` is epoch milliseconds set using the actual saved Gateway receipt time, not the example constant above. Null sensor fields are omitted.

Typical CoreIOT/ThingsBoard server-side RPC on `v1/devices/me/rpc/request/{requestId}`:
```json
{"method":"mute_buzzer","params":{"mute":true}}
```
Member 2 turns it into a ColdGuard command and carries the cloud request ID through the bridge. Reply only on the paired CoreIOT RPC response topic after the device ACK (or return a clear timeout/error response).

## Week 1 acceptance
- **M1:** Build firmware with sample telemetry and publish valid JSON to local broker.
- **M2:** Subscribe to both telemetry topics, validate with schema, save to SQLite; provide a simulator.
- **M3:** Create CoreIOT test devices and confirm normalized fields/dashboard; keep Tasmota payload mapping separately.

## Compatibility
If any key, unit, or message shape changes, bump `v` and notify all 3 members before merging changes. Do not silently rename JSON keys.
