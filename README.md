# ESP32-ESP8266-HTTP

Simple HTTP server for ESP32 and ESP8266 with DHT11 temperature and humidity sensor.


## Requisites

Create a file named `WiFiCredentials.h` and add the following content to it:
```
#ifndef WiFiCredentials_h
#define WiFiCredentials_h

#define WIFI_SSID "XXXXX"
#define WIFI_PASSWORD "XXXXXXXXXXX"

#endif
```

Be sure to modify the `WIFI_SSID` and `WIFI_PASSWORD` constants with your wifi information.

Make a `GET` request to `http://<esp-ip>/` to retrieve the data.
