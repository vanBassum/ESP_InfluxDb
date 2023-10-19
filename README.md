# ESP_InfluxDb

ESP_InfluxDb is a library designed to facilitate the seamless integration of InfluxDb V2 with the ESP-IDF framework. This library simplifies the process of pushing data to InfluxDb by leveraging the ESP-IDF HTTP client.

## Motivation

While attempting to find a suitable library for ESP-IDF to work with InfluxDb V2, I encountered a lack of comprehensive solutions. Although I initially tried porting an Arduino library, the process proved cumbersome due to heavy reliance on Arduino-specific APIs. To address this, I opted to create a new library from the ground up, utilizing the ESP-IDF HTTP client for optimal compatibility.

## Usage

To get started quickly, here's a minimal code example:

```cpp
#include "InfluxDb.h"

#define INFLUXDB_URL "MyUrl.com"
#define INFLUXDB_TOKEN "MyToken"
#define INFLUXDB_ORG "MyOrganisation"
#define INFLUXDB_BUCKET "MyBucket"

Influx::Client client(INFLUXDB_URL, INFLUXDB_TOKEN, INFLUXDB_ORG, INFLUXDB_BUCKET);

Influx::Point("MyMeasurement")
  .AddTag("Sensor", "DS18B20")		
  .AddField("Temp", 12.6f)
  .SetTimestamp(1697727036000000000)
  .Post(client);
```


Certainly, you can emphasize the TLS considerations in the README. Here's an updated section for that:

## TLS Considerations

For the time being, TLS is not enabled in this library. Altought adding TLS is expected to be a straightforward process, it hasn't been implemented yet. Attempts to use the X509 bundle for TLS verification encountered memory constraints.

During testing, you can disable TLS verification by following these steps:

1. Open the MenuConfig.
2. Under ESP-TLS, enable 'Allow potentially insecure options.'
3. Under ESP-TLS, enable 'Skip server certificate verification by default.'

Keep in mind that this is for testing purposes only, and in a production environment, enabling TLS verification is crucial for security. Contributions to implement TLS or any other enhancements are welcome, and your feedback is highly appreciated!

## Querying Data

At present, querying data from InfluxDb is not a feature included in this library. While it's a potential addition for the future, it's not in the current development scope. If querying functionality is crucial for your project, you may need to explore alternative solutions or consider contributing to the library's development.

## TODO

- [x] Write data points to InfluxDb V2
- [ ] Add TLS verification

Feel free to contribute or provide feedback to help improve the functionality and robustness of this library. Your input is highly valued!
