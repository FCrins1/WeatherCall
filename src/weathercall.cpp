#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "weathercall.h"





#define DEBUG

#ifndef DEBUG_PRINT
  #ifdef DEBUG
    #define DEBUG_PRINT(x)  Serial.println (x)
  #else
    #define DEBUG_PRINT(x)
  #endif
#endif





Weathercall::Weathercall(String Key, String City){
  //_Key = Key;
  //_City = City;
  _forecast = false;
  _url = "/data/2.5/weather?q=" + City + "&appid=" + Key +"&units=metric";
}

Weathercall::Weathercall(String Key, float lat, float longi){
  //_Key = Key;
  //_City = City;
  _forecast = false;
  _url = "/data/2.5/weather?lat=" + String(lat) + "&long=" + String(longi) + "&appid=" + Key +"&units=metric";
}

Weathercall::Weathercall(String Key, String City, boolean forecast){
  //_Key = Key;
  //_City = City;
  _forecast = forecast;
  if(!forecast)
    _url = "/data/2.5/weather?q=" + City + "&appid=" + Key +"&units=metric&cnt=1";
  else
    _url = "/data/2.5/forecast?q=" + City + "&appid=" + Key +"&units=metric&cnt=10";
}








void Weathercall::updateStatus(weatherData *w){
  //httpsClient.setFingerprint(fingerprint);
  const char *openweather = "api.openweathermap.org";
  const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
  WiFiClientSecure httpsClient;
  //const size_t capacity = 2*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(2) + 6*JSON_OBJECT_SIZE(1) + 3*JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 5*JSON_OBJECT_SIZE(8) + 570;
  httpsClient.setInsecure();
  httpsClient.setTimeout(15000); // 15 Seconds
  delay(1000);

  //Serial.print("HTTPS Connecting");
  int r=0; //retry counter
  while((!httpsClient.connect(openweather, httpsPort)) && (r < 30)){
      delay(100);
      Serial.print(".");
      r++;
  }

  DEBUG_PRINT("requesting URL: ");
  DEBUG_PRINT(openweather+_url);

  httpsClient.print(String("GET ") + _url + " HTTP/1.1\r\n" +
               "Host: " + openweather + "\r\n" +
               "Connection: close\r\n\r\n");

  DEBUG_PRINT("request sent");

  while (httpsClient.connected()) {
    _Response = httpsClient.readStringUntil('\n');
    if (_Response == "\r") {
      DEBUG_PRINT("headers received");
      DEBUG_PRINT(_Response);
      break;
    }
  }

  DEBUG_PRINT("reply was:");
  DEBUG_PRINT("==========");
  //httpsClient.readStringUntil('\n'); // The API sends an extra line with just a number. This breaks the JSON parsing, hence an extra read
  while(httpsClient.connected()){
    _Response = httpsClient.readString();
    DEBUG_PRINT(_Response); //Print response
  }
  JsonDocument doc;
  deserializeJson(doc,_Response);
  if(!_forecast){
    w->description = doc["weather"][0]["description"].as<String>();
    w->weather = doc["weather"][0]["main"].as<String>();
    w->id = doc["weather"][0]["id"].as<int>();
    w->current_Temp = doc["main"]["temp"].as<float>();
    w->min_temp = doc["main"]["temp_min"].as<float>();
    w->max_temp = doc["main"]["temp_max"].as<float>();
    w->humidity = doc["main"]["humidity"].as<int>();
    w->pressure = doc["main"]["pressure"].as<int>();
    w->windspeed = doc["wind"]["speed"].as<float>();
    w->windeg = doc["wind"]["deg"].as<int>();
    w->cloud = doc["clouds"]["all"].as<int>();
    w->Location = doc["name"].as<String>();
    w->Country = doc["sys"]["country"].as<String>();
    w->icon = doc["weather"][0]["icon"].as<String>();
    w->sunrise = doc["sys"]["sunrise"].as<long>();
    w->sunset = doc["sys"]["sunset"].as<long>();
    w->dt = doc["dt"].as<int>();
    w->timezone = doc["timezone"].as<int>();
    if(w->id <600) w->rain = doc["rain"]["1h"].as<float>();
    else if (w->id <700) w->rain1 = doc["Snow"]["1h"].as<float>();
    else w->rain = 0;

  } else
  {
    // Currently set to get forecast 10 X 3h hours from now
    w->description1 = doc["list"][0]["weather"][0]["description"].as<String>(); 
    w->weather1 = doc["list"][0]["weather"][0]["main"].as<String>();
    w->id1 = doc["list"][0]["weather"][0]["id"].as<int>();
    w->current_Temp1 = doc["list"][0]["main"]["temp"].as<float>();
    w->min_temp1 = doc["list"][0]["main"]["temp_min"].as<float>();
    w->max_temp1 = doc["list"][0]["main"]["temp_max"].as<float>();
    w->humidity1 = doc["list"][0]["main"]["humidity"].as<int>();
    w->pressure1 = doc["list"][0]["main"]["pressure"].as<int>();
    w->windspeed1 = doc["list"][0]["wind"]["speed"].as<float>();
    w->windeg1 = doc["list"][0]["wind"]["deg"].as<int>();
    w->cloud1 = doc["list"][0]["clouds"]["all"].as<int>();
    w->icon1 = doc["list"][0]["weather"][0]["icon"].as<String>();
    w->dt_txt1 = doc["list"][0]["dt_txt"].as<String>();
    if(w->id1 <600) w->rain1 = doc["list"][0]["rain"]["3h"].as<float>();
    else if (w->id1 <700) w->rain1 = doc["list"][0]["snow"]["3h"].as<float>();
    else w->rain1 = 0;


    w->description2 = doc["list"][1]["weather"][0]["description"].as<String>(); 
    w->weather2 = doc["list"][1]["weather"][0]["main"].as<String>();
    w->id2 = doc["list"][1]["weather"][0]["id"].as<int>();
    w->current_Temp2 = doc["list"][1]["main"]["temp"].as<float>();
    w->min_temp2 = doc["list"][1]["main"]["temp_min"].as<float>();
    w->max_temp2 = doc["list"][1]["main"]["temp_max"].as<float>();
    w->humidity2 = doc["list"][1]["main"]["humidity"].as<int>();
    w->pressure2 = doc["list"][1]["main"]["pressure"].as<int>();
    w->windspeed2 = doc["list"][1]["wind"]["speed"].as<float>();
    w->windeg2 = doc["list"][1]["wind"]["deg"].as<int>();
    w->cloud2 = doc["list"][1]["clouds"]["all"].as<int>();
    w->icon2 = doc["list"][1]["weather"][0]["icon"].as<String>();
    w->dt_txt2 = doc["list"][1]["dt_txt"].as<String>();
    if(w->id2 <600) w->rain2 = doc["list"][1]["rain"]["3h"].as<float>();
    else if (w->id2 <700) w->rain2 = doc["list"][1]["snow"]["3h"].as<float>();
    else w->rain2 = 0;


    w->description3 = doc["list"][2]["weather"][0]["description"].as<String>(); 
    w->weather3 = doc["list"][2]["weather"][0]["main"].as<String>();
    w->id3 = doc["list"][2]["weather"][0]["id"].as<int>();
    w->current_Temp3 = doc["list"][2]["main"]["temp"].as<float>();
    w->min_temp3 = doc["list"][2]["main"]["temp_min"].as<float>();
    w->max_temp3 = doc["list"][2]["main"]["temp_max"].as<float>();
    w->humidity3 = doc["list"][2]["main"]["humidity"].as<int>();
    w->pressure3 = doc["list"][2]["main"]["pressure"].as<int>();
    w->windspeed3 = doc["list"][2]["wind"]["speed"].as<float>();
    w->windeg3 = doc["list"][2]["wind"]["deg"].as<int>();
    w->cloud3 = doc["list"][2]["clouds"]["all"].as<int>();
    w->icon3 = doc["list"][2]["weather"][0]["icon"].as<String>();
    w->dt_txt3 = doc["list"][2]["dt_txt"].as<String>();
    if(w->id3 <600) w->rain3 = doc["list"][2]["rain"]["3h"].as<float>();
    else if (w->id3 <700) w->rain3 = doc["list"][2]["snow"]["3h"].as<float>();
    else w->rain3 = 0;

    w->description4 = doc["list"][3]["weather"][0]["description"].as<String>(); 
    w->weather4 = doc["list"][3]["weather"][0]["main"].as<String>();
    w->id4 = doc["list"][3]["weather"][0]["id"].as<int>();
    w->current_Temp4 = doc["list"][3]["main"]["temp"].as<float>();
    w->min_temp4 = doc["list"][3]["main"]["temp_min"].as<float>();
    w->max_temp4 = doc["list"][3]["main"]["temp_max"].as<float>();
    w->humidity4 = doc["list"][3]["main"]["humidity"].as<int>();
    w->pressure4 = doc["list"][3]["main"]["pressure"].as<int>();
    w->windspeed4 = doc["list"][3]["wind"]["speed"].as<float>();
    w->windeg4 = doc["list"][3]["wind"]["deg"].as<int>();
    w->cloud4 = doc["list"][3]["clouds"]["all"].as<int>();
    w->icon4 = doc["list"][3]["weather"][0]["icon"].as<String>();
    w->dt_txt4 = doc["list"][3]["dt_txt"].as<String>();
    if(w->id4 <600) w->rain4 = doc["list"][3]["rain"]["3h"].as<float>();
    else if (w->id4 <700) w->rain4 = doc["list"][3]["snow"]["3h"].as<float>();
    else w->rain4 = 0;

    w->description5 = doc["list"][4]["weather"][0]["description"].as<String>(); 
    w->weather5 = doc["list"][4]["weather"][0]["main"].as<String>();
    w->id5 = doc["list"][4]["weather"][0]["id"].as<int>();
    w->current_Temp5 = doc["list"][4]["main"]["temp"].as<float>();
    w->min_temp5 = doc["list"][4]["main"]["temp_min"].as<float>();
    w->max_temp5 = doc["list"][4]["main"]["temp_max"].as<float>();
    w->humidity5 = doc["list"][4]["main"]["humidity"].as<int>();
    w->pressure5 = doc["list"][4]["main"]["pressure"].as<int>();
    w->windspeed5 = doc["list"][4]["wind"]["speed"].as<float>();
    w->windeg5 = doc["list"][4]["wind"]["deg"].as<int>();
    w->cloud5 = doc["list"][4]["clouds"]["all"].as<int>();
    w->icon5 = doc["list"][4]["weather"][0]["icon"].as<String>();
    w->dt_txt5 = doc["list"][4]["dt_txt"].as<String>();
    if(w->id5 <600) w->rain5 = doc["list"][4]["rain"]["3h"].as<float>();
    else if (w->id5 <700) w->rain5 = doc["list"][4]["snow"]["3h"].as<float>();
    else w->rain5 = 0;

    w->description6 = doc["list"][5]["weather"][0]["description"].as<String>(); 
    w->weather6 = doc["list"][5]["weather"][0]["main"].as<String>();
    w->id6 = doc["list"][5]["weather"][0]["id"].as<int>();
    w->current_Temp6 = doc["list"][5]["main"]["temp"].as<float>();
    w->min_temp6 = doc["list"][5]["main"]["temp_min"].as<float>();
    w->max_temp6 = doc["list"][5]["main"]["temp_max"].as<float>();
    w->humidity6 = doc["list"][5]["main"]["humidity"].as<int>();
    w->pressure6 = doc["list"][5]["main"]["pressure"].as<int>();
    w->windspeed6 = doc["list"][5]["wind"]["speed"].as<float>();
    w->windeg6 = doc["list"][5]["wind"]["deg"].as<int>();
    w->cloud6 = doc["list"][5]["clouds"]["all"].as<int>();
    w->icon6 = doc["list"][5]["weather"][0]["icon"].as<String>();
    w->dt_txt6 = doc["list"][5]["dt_txt"].as<String>();
    if(w->id6 <600) w->rain6 = doc["list"][5]["rain"]["3h"].as<float>();
    else if (w->id6 <700) w->rain6 = doc["list"][5]["snow"]["3h"].as<float>();
    else w->rain6 = 0;

    w->description7 = doc["list"][6]["weather"][0]["description"].as<String>(); 
    w->weather7 = doc["list"][6]["weather"][0]["main"].as<String>();
    w->id7 = doc["list"][6]["weather"][0]["id"].as<int>();
    w->current_Temp7 = doc["list"][6]["main"]["temp"].as<float>();
    w->min_temp7 = doc["list"][6]["main"]["temp_min"].as<float>();
    w->max_temp7 = doc["list"][6]["main"]["temp_max"].as<float>();
    w->humidity7 = doc["list"][6]["main"]["humidity"].as<int>();
    w->pressure7 = doc["list"][6]["main"]["pressure"].as<int>();
    w->windspeed7 = doc["list"][6]["wind"]["speed"].as<float>();
    w->windeg7 = doc["list"][6]["wind"]["deg"].as<int>();
    w->cloud7 = doc["list"][6]["clouds"]["all"].as<int>();
    w->icon7 = doc["list"][6]["weather"][0]["icon"].as<String>();
    w->dt_txt7 = doc["list"][6]["dt_txt"].as<String>();
    if(w->id7 <600) w->rain7 = doc["list"][6]["rain"]["3h"].as<float>();
    else if (w->id7 <700) w->rain7 = doc["list"][6]["snow"]["3h"].as<float>();
    else w->rain7 = 0;

        w->description8 = doc["list"][7]["weather"][0]["description"].as<String>(); 
    w->weather8 = doc["list"][7]["weather"][0]["main"].as<String>();
    w->id8 = doc["list"][7]["weather"][0]["id"].as<int>();
    w->current_Temp8 = doc["list"][7]["main"]["temp"].as<float>();
    w->min_temp8 = doc["list"][7]["main"]["temp_min"].as<float>();
    w->max_temp8 = doc["list"][7]["main"]["temp_max"].as<float>();
    w->humidity8 = doc["list"][7]["main"]["humidity"].as<int>();
    w->pressure8 = doc["list"][7]["main"]["pressure"].as<int>();
    w->windspeed8 = doc["list"][7]["wind"]["speed"].as<float>();
    w->windeg8 = doc["list"][7]["wind"]["deg"].as<int>();
    w->cloud8 = doc["list"][7]["clouds"]["all"].as<int>();
    w->icon8 = doc["list"][7]["weather"][0]["icon"].as<String>();
    w->dt_txt8 = doc["list"][7]["dt_txt"].as<String>();
    if(w->id8 <600) w->rain8 = doc["list"][7]["rain"]["3h"].as<float>();
    else if (w->id8 <700) w->rain8 = doc["list"][7]["snow"]["3h"].as<float>();
    else w->rain8 = 0;

        w->description9 = doc["list"][8]["weather"][0]["description"].as<String>(); 
    w->weather9 = doc["list"][8]["weather"][0]["main"].as<String>();
    w->id9 = doc["list"][8]["weather"][0]["id"].as<int>();
    w->current_Temp9 = doc["list"][8]["main"]["temp"].as<float>();
    w->min_temp9 = doc["list"][8]["main"]["temp_min"].as<float>();
    w->max_temp9 = doc["list"][8]["main"]["temp_max"].as<float>();
    w->humidity9 = doc["list"][8]["main"]["humidity"].as<int>();
    w->pressure9 = doc["list"][8]["main"]["pressure"].as<int>();
    w->windspeed9 = doc["list"][8]["wind"]["speed"].as<float>();
    w->windeg9 = doc["list"][8]["wind"]["deg"].as<int>();
    w->cloud9 = doc["list"][8]["clouds"]["all"].as<int>();
    w->icon9 = doc["list"][8]["weather"][0]["icon"].as<String>();
    w->dt_txt9 = doc["list"][8]["dt_txt"].as<String>();
    if(w->id9 <600) w->rain9 = doc["list"][8]["rain"]["3h"].as<float>();
    else if (w->id9 <700) w->rain9 = doc["list"][8]["snow"]["3h"].as<float>();
    else w->rain9 = 0;

        w->description10 = doc["list"][9]["weather"][0]["description"].as<String>(); 
    w->weather10 = doc["list"][9]["weather"][0]["main"].as<String>();
    w->id10 = doc["list"][9]["weather"][0]["id"].as<int>();
    w->current_Temp10 = doc["list"][9]["main"]["temp"].as<float>();
    w->min_temp10 = doc["list"][9]["main"]["temp_min"].as<float>();
    w->max_temp10 = doc["list"][9]["main"]["temp_max"].as<float>();
    w->humidity10 = doc["list"][9]["main"]["humidity"].as<int>();
    w->pressure10 = doc["list"][9]["main"]["pressure"].as<int>();
    w->windspeed10 = doc["list"][9]["wind"]["speed"].as<float>();
    w->windeg10 = doc["list"][9]["wind"]["deg"].as<int>();
    w->cloud10 = doc["list"][9]["clouds"]["all"].as<int>();
    w->icon10 = doc["list"][9]["weather"][0]["icon"].as<String>();
    w->dt_txt10 = doc["list"][9]["dt_txt"].as<String>();
    if(w->id10 <600) w->rain10 = doc["list"][9]["rain"]["3h"].as<float>();
    else if (w->id10 <700) w->rain10 = doc["list"][9]["snow"]["3h"].as<float>();
    else w->rain10 = 0;
  }
}
String Weathercall::getResponse(){
  return _Response;
}