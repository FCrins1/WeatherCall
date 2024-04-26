#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include  <weathercall.h>

//**************************************SETTINGS******************************************************
// Replace with your wifi credentials
const char * ssid = "XXXXXXXXXXXXXXXXXXS";
const char * password = "YYYYYYYYYYYYY";

// Get and API Key by registering on
// https://openweathermap.org/apiS

String Key = "ZZZZZZZZZZZZ";
// Example:
//String Key = "82ded39778699b0514b9d169486b1ae5";

// Replace with your country code and city
String city = "Liege";
String countryCode = "be";

//******************************************************************************************
String jsonBuffer;

weatherData w;
Weathercall weather(Key, "Liege,be");
Weathercall forecast(Key, "Liege,be",1);

String timconv (long epoc ){
    int secondo = epoc % 60;
    int minus = (epoc / 60);
    int minuto = minus %60;
    int hrus = minus /60;
    int horus = hrus %24;
    //int dayys = hrus /24;
    String uptimus =String(horus) + ":" + String(minuto) + ":" + String(secondo);
    return uptimus;
}

void setup() {
  // put your setup code here, to run once:
      Serial.begin(115200);
    Serial.setDebugOutput(true);
    log_i("Board: %s", BOARD_NAME);
    log_i("CPU: %s rev%d, CPU Freq: %d Mhz, %d core(s)", ESP.getChipModel(), ESP.getChipRevision(), getCpuFrequencyMhz(), ESP.getChipCores());
    log_i("Free heap: %d bytes", ESP.getFreeHeap());
    log_i("Free PSRAM: %d bytes", ESP.getPsramSize());
    log_i("SDK version: %s", ESP.getSdkVersion());
    
     delay(500);
  //Serial.println(ssid);
  //Serial.println(password);
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
      delay(2000);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }


    Serial.println();
    Serial.println("WiFi connected");
    Serial.println("IP address: "); Serial.println(WiFi.localIP());
    Serial.print("Chip num:\t");
    Serial.println(ESP.getEfuseMac());
    Serial.print("Hostname:\t");
    Serial.println(WiFi.getHostname());
    Serial.print("Connected to SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());

}


String Wind_NWES_direction(int windegree){
    /////////////////////Wind degree to NSEW value 
    String direction;
        switch (windegree) {
            
          case 337 ... 359:
           direction = "N";
          break;
          
          case 0 ... 23 :
          direction = "N";
          break;

          case 24 ... 68:
          direction = "NE";
          break;

          case 69 ... 113:
          direction = "E";
          break;

          case 114 ... 158:
           direction = "SE";
          break;
          
          case 159 ... 203 :
          direction = "S";
          break;

          case 204 ... 248:
          direction = "SW";
          break;

          case 249 ... 293:
          direction = "W";
          break;

          case 294 ... 336:
          direction = "NW";
          break;

          default: 
          // if nothing else matches, do the default
          // default is optional
          direction = "?";
          break;
      }
    return direction;

}

void Weatherupdatescreen(){
        /////////////////////variable to screen label
        Serial.print("Weather and Description: ");
        Serial.println(w.weather + ": " + w.description);
        Serial.print("Temperature in °C: ");
        Serial.println(w.current_Temp);
        Serial.print("Temperature Min °C: ");
        Serial.println(w.min_temp);
        Serial.print("Temperature Max °C: ");
        Serial.println(w.max_temp);
        Serial.print("Humidity %: ");
        Serial.println(w.humidity);
        Serial.print("Pressure hPa: ");
        Serial.println(w.pressure);
        Serial.print("Wind Direction / Speed km/h: ");
        Serial.println(Wind_NWES_direction(w.windeg) +" "+ (w.windspeed*3.6));
        Serial.print("Clouds %: ");
        Serial.println(w.cloud);
        Serial.print("Rains in mm (or snow): ");
        Serial.println(w.rain);
        Serial.print("Location/Country ");
        Serial.println(w.Location + "," + w.Country);
        Serial.print("Sunrise");
        Serial.println(timconv(w.sunrise + w.timezone));
        Serial.print("Sunset");
        Serial.println(timconv(w.sunset + w.timezone));
        Serial.print("last updated: ");
        Serial.println(timconv(w.dt+ w.timezone));
        Serial.print("Full Response1: ");
        Serial.println(weather.getResponse().c_str());

}

void Forecastupdatescreen(){

        Serial.print("Time Date: ");
        Serial.println(w.dt_txt1);
        Serial.print("Weather and Description 1: ");
        Serial.println(w.weather1 + ": " + w.description1);
        Serial.print("Temperature in °C 1: ");
        Serial.println(w.current_Temp1);
        Serial.print("Temperature Min °C 1: ");
        Serial.println(w.min_temp1);
        Serial.print("Temperature Max °C 1: ");
        Serial.println(w.max_temp1);
        Serial.print("Humidity % 1: ");
        Serial.println(w.humidity1);
        Serial.print("Pressure hPa 1: ");
        Serial.println(w.pressure1);
        Serial.print("Wind Direction / Speed km/h 1: ");
        Serial.println(Wind_NWES_direction(w.windeg1) +" "+ (w.windspeed1*3.6));
        Serial.print("Clouds % 1: ");
        Serial.println(w.cloud1);
        Serial.print("Rains in mm (or snow) 1: ");
        Serial.println(w.rain1);
        
        Serial.println();
        Serial.print("Time Date: ");
        Serial.println(w.dt_txt2);
        Serial.print("Weather and Description 2: ");
        Serial.println(w.weather2 + ": " + w.description2);
        Serial.print("Temperature in °C 2: ");
        Serial.println(w.current_Temp2);
        Serial.print("Temperature Min °C 2: ");
        Serial.println(w.min_temp2);
        Serial.print("Temperature Max °C 2: ");
        Serial.println(w.max_temp2);
        Serial.print("Humidity % 2: ");
        Serial.println(w.humidity2);
        Serial.print("Pressure hPa 2: ");
        Serial.println(w.pressure2);
        Serial.print("Wind Direction / Speed km/h 2: ");
        Serial.println(Wind_NWES_direction(w.windeg2) +" "+ (w.windspeed2*3.6));
        Serial.print("Clouds % 2: ");
        Serial.println(w.cloud2);
        Serial.print("Rains in mm (or snow) 2: ");
        Serial.println(w.rain2);        
        
        Serial.println();
        Serial.print("Time Date: ");
        Serial.println(w.dt_txt3);
        Serial.print("Weather and Description 3: ");
        Serial.println(w.weather3 + ": " + w.description3);
        Serial.print("Temperature in °C 3: ");
        Serial.println(w.current_Temp3);
        Serial.print("Temperature Min °C 3: ");
        Serial.println(w.min_temp3);
        Serial.print("Temperature Max °C 3: ");
        Serial.println(w.max_temp3);
        Serial.print("Humidity % 3: ");
        Serial.println(w.humidity3);
        Serial.print("Pressure hPa 3: ");
        Serial.println(w.pressure3);
        Serial.print("Wind Direction / Speed km/h 3: ");
        Serial.println(Wind_NWES_direction(w.windeg3) +" "+ (w.windspeed3*3.6));
        Serial.print("Clouds % 3: ");
        Serial.println(w.cloud3);
        Serial.print("Rains in mm (or snow) 3: ");
        Serial.println(w.rain3);      
        Serial.print("Full Response1: ");
        Serial.println(forecast.getResponse().c_str());
        
        Serial.println();
        Serial.print("Time Date: ");
        Serial.println(w.dt_txt4);
        Serial.print("Weather and Description 4: ");
        Serial.println(w.weather4 + ": " + w.description4);
        Serial.print("Temperature in °C 4: ");
        Serial.println(w.current_Temp4);
        Serial.print("Temperature Min °C 4: ");
        Serial.println(w.min_temp4);
        Serial.print("Temperature Max °C 4: ");
        Serial.println(w.max_temp4);
        Serial.print("Humidity % 4: ");
        Serial.println(w.humidity4);
        Serial.print("Pressure hPa 4: ");
        Serial.println(w.pressure4);
        Serial.print("Wind Direction / Speed km/h 4: ");
        Serial.println(Wind_NWES_direction(w.windeg4) +" "+ (w.windspeed4*3.6));
        Serial.print("Clouds % 4: ");
        Serial.println(w.cloud4);
        Serial.print("Rains in mm (or snow) 4: ");
        Serial.println(w.rain4);      
        
        Serial.println();
        Serial.print("Time Date: ");
        Serial.println(w.dt_txt5);
        Serial.print("Weather and Description 5: ");
        Serial.println(w.weather5 + ": " + w.description5);
        Serial.print("Temperature in °C 5: ");
        Serial.println(w.current_Temp5);
        Serial.print("Temperature Min °C 5: ");
        Serial.println(w.min_temp5);
        Serial.print("Temperature Max °C 5: ");
        Serial.println(w.max_temp5);
        Serial.print("Humidity % 5: ");
        Serial.println(w.humidity5);
        Serial.print("Pressure hPa 5: ");
        Serial.println(w.pressure5);
        Serial.print("Wind Direction / Speed km/h 5: ");
        Serial.println(Wind_NWES_direction(w.windeg5) +" "+ (w.windspeed5*3.6));
        Serial.print("Clouds % 5: ");
        Serial.println(w.cloud5);
        Serial.print("Rains in mm (or snow) 5: ");
        Serial.println(w.rain5);
        
        Serial.println();
        Serial.print("Time Date: ");
        Serial.println(w.dt_txt6);
        Serial.print("Weather and Description 6: ");
        Serial.println(w.weather6 + ": " + w.description6);
        Serial.print("Temperature in °C 6: ");
        Serial.println(w.current_Temp6);
        Serial.print("Temperature Min °C 6: ");
        Serial.println(w.min_temp6);
        Serial.print("Temperature Max °C 6: ");
        Serial.println(w.max_temp6);
        Serial.print("Humidity % 6: ");
        Serial.println(w.humidity6);
        Serial.print("Pressure hPa 6: ");
        Serial.println(w.pressure6);
        Serial.print("Wind Direction / Speed km/h 6: ");
        Serial.println(Wind_NWES_direction(w.windeg6) +" "+ (w.windspeed6*3.6));
        Serial.print("Clouds % 6: ");
        Serial.println(w.cloud6);
        Serial.print("Rains in mm (or snow) 6: ");
        Serial.println(w.rain6);
        
        Serial.println();
        Serial.print("Time Date: ");
        Serial.println(w.dt_txt7);
        Serial.print("Weather and Description 7: ");
        Serial.println(w.weather7 + ": " + w.description7);
        Serial.print("Temperature in °C 7: ");
        Serial.println(w.current_Temp7);
        Serial.print("Temperature Min °C 7: ");
        Serial.println(w.min_temp7);
        Serial.print("Temperature Max °C 7: ");
        Serial.println(w.max_temp7);
        Serial.print("Humidity % 7: ");
        Serial.println(w.humidity7);
        Serial.print("Pressure hPa 7: ");
        Serial.println(w.pressure7);
        Serial.print("Wind Direction / Speed km/h 7: ");
        Serial.println(Wind_NWES_direction(w.windeg7) +" "+ (w.windspeed7*3.6));
        Serial.print("Clouds % 7: ");
        Serial.println(w.cloud7);
        Serial.print("Rains in mm (or snow) 7: ");
        Serial.println(w.rain7);
        
        Serial.println();        
        Serial.print("Time Date: ");
        Serial.println(w.dt_txt8);
        Serial.print("Weather and Description 8: ");
        Serial.println(w.weather8 + ": " + w.description8);
        Serial.print("Temperature in °C 8: ");
        Serial.println(w.current_Temp8);
        Serial.print("Temperature Min °C 8: ");
        Serial.println(w.min_temp8);
        Serial.print("Temperature Max °C 8: ");
        Serial.println(w.max_temp8);
        Serial.print("Humidity % 8: ");
        Serial.println(w.humidity8);
        Serial.print("Pressure hPa 8: ");
        Serial.println(w.pressure8);
        Serial.print("Wind Direction / Speed km/h 8: ");
        Serial.println(Wind_NWES_direction(w.windeg8) +" "+ (w.windspeed8*3.6));
        Serial.print("Clouds % 8: ");
        Serial.println(w.cloud8);
        Serial.print("Rains in mm (or snow) 8: ");
        Serial.println(w.rain8);
        
        Serial.println();
        Serial.print("Time Date: ");
        Serial.println(w.dt_txt9);
        Serial.print("Weather and Description 9: ");
        Serial.println(w.weather9 + ": " + w.description9);
        Serial.print("Temperature in °C 9: ");
        Serial.println(w.current_Temp9);
        Serial.print("Temperature Min °C 9: ");
        Serial.println(w.min_temp9);
        Serial.print("Temperature Max °C 9: ");
        Serial.println(w.max_temp9);
        Serial.print("Humidity % 9: ");
        Serial.println(w.humidity9);
        Serial.print("Pressure hPa 9: ");
        Serial.println(w.pressure9);
        Serial.print("Wind Direction / Speed km/h 9: ");
        Serial.println(Wind_NWES_direction(w.windeg9) +" "+ (w.windspeed9*3.6));
        Serial.print("Clouds % 9: ");
        Serial.println(w.cloud9);
        Serial.print("Rains in mm (or snow) 9: ");
        Serial.println(w.rain9);

        Serial.println();
        Serial.print("Time Date: ");
        Serial.println(w.dt_txt10);
        Serial.print("Weather and Description 10: ");
        Serial.println(w.weather10 + ": " + w.description10);
        Serial.print("Temperature in °C 10: ");
        Serial.println(w.current_Temp10);
        Serial.print("Temperature Min °C 10: ");
        Serial.println(w.min_temp10);
        Serial.print("Temperature Max °C 10: ");
        Serial.println(w.max_temp10);
        Serial.print("Humidity % 10: ");
        Serial.println(w.humidity10);
        Serial.print("Pressure hPa 10: ");
        Serial.println(w.pressure10);
        Serial.print("Wind Direction / Speed km/h 10: ");
        Serial.println(Wind_NWES_direction(w.windeg10) +" "+ (w.windspeed10*3.6));
        Serial.print("Clouds % 10: ");
        Serial.println(w.cloud10);
        Serial.print("Rains in mm (or snow) 10: ");
        Serial.println(w.rain10);
        Serial.println();
        Serial.println();

        Serial.print("Full Response1: ");
        Serial.println(forecast.getResponse().c_str());
}

ulong min10_millistime = 2000;
ulong Hourly_millis = 3000;
ulong next_millis = 1000;

void loop() {
  // put your main code here, to run repeatedly:
  auto const now = millis();

    if (now > next_millis){

    }

    if (now > min10_millistime)
    {
        min10_millistime = now + 600000;
        weather.updateStatus(&w);   

        Weatherupdatescreen();
         
               
      }

    if (now > Hourly_millis){
         forecast.updateStatus(&w);
        Forecastupdatescreen();
        Hourly_millis = Hourly_millis + 3600000;
////////////////////////////////////////////////////////
   

        
    }


}



