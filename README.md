# WeatherCall
<p align="center">

</p>
Required : ArduinoJson <a href="https://arduinojson.org/">.

## Features
Library to get current weather and forecast from openweather in various variables, inspired by dushyantahuja/SimpleWeather; tested on ESP32. Require ArduinoJson. 
10 times 3h forecast in 14 weather forecast variable. 
19 current weather variable. 
## Quickstart

### WeatherCall

Here is a simple call

```c++
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include  <weathercall.h>

weatherData w;
Weathercall weather(Key, "Liege,be");
Weathercall forecast(Key, "Liege,be",1);

....
void loop() {
weather.updateStatus(&w);
forecast.updateStatus(&w);
...
Serial.print("Weather and Description: ");
Serial.println(w.weather + ": " + w.description);
Serial.print("Temperature in °C: ");
Serial.println(w.current_Temp);
...
Serial.print("Time Date: ");
Serial.println(w.dt_txt1);
Serial.print("Weather and Description 1: ");
Serial.println(w.weather1 + ": " + w.description1);
Serial.print("Temperature in °C 1: ");
Serial.println(w.current_Temp1);
}

```

See the Tutorial : (Coming soon)

## Sponsors

WeatherCall is thankful to its sponsors. Please give them a visit; they deserve it!

<p>
  <a href="https://www.pNutongroup/" rel="sponsored">
      </a>
</p>
<p>
  <a href="https://github.com/1technophile" rel="sponsored">
   
  </a>
</p>
