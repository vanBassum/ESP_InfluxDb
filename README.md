
# ESPHome InfluxDB Writer Component

This repository contains a custom ESPHome component that posts sensor data to an InfluxDB 2.x instance using HTTP.


## Features

- Subscribes to all non-internal sensors in ESPHome.
- Sends sensor data in [InfluxDB line protocol](https://docs.influxdata.com/influxdb/latest/reference/syntax/line-protocol/) format.
- Includes timestamps in seconds.

## Configuration Example

```yaml
esphome:
  name: testjec3
  friendly_name: TestjeC3

esp32:
  board: esp32dev
  framework:
    type: esp-idf

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

external_components:
  - source:
      type: git
      url: https://github.com/vanBassum/ESP_InfluxDb
      
sensor: 
  - platform: uptime
    name: "Uptime"

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

## Secrets Example

```yaml
wifi_ssid: "MyWifiSSID"
wifi_password: "WyWifiPassword"
influxdb_url: http://MyInfluxServer.com:8086/api/v2/write
influxdb_token: MyInfluxApiKey=
influxdb_org: MyOrganisation
influxdb_bucket: MyBucket
```
