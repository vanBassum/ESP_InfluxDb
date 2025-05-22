
# ESPHome InfluxDB Writer Component

This repository contains a custom ESPHome component that posts sensor data to an InfluxDB 2.x instance using HTTP.


---

## Features

- Subscribes to all non-internal sensors in ESPHome.
- Sends sensor data in [InfluxDB line protocol](https://docs.influxdata.com/influxdb/latest/reference/syntax/line-protocol/) format.
- Includes timestamps in seconds.



## Configuration Example

```yaml
esphome:
  name: myInflux
  platform: esp32
  board: esp32-c3-devkitm-1

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

http_request:
  id: http_component
  useragent: esphome-influx
  timeout: 10s

influxdb:
  url: !secret influxdb_url
  token: !secret influxdb_token
  org: !secret influxdb_org
  bucket: !secret influxdb_bucket
  measurement: esp_data
  http_request_id: http_component
```
