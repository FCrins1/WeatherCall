

/*
  Weathercall.cpp - Library to get weather from Openweather
  Improved by 
  Created by Dushyant Ahuja, September 2019.
  Released into the public domain.
*/
#ifndef weathercall_h
#define weathercall_h

#include "Arduino.h"


struct weatherData{
  String weather;
  String description;
  String icon;
  String Location;
  String Country;
  int id;
  int timezone;
  int windeg;
  int cloud;
  float windspeed;
  long dt;
  long sunrise;
  long sunset;
  float current_Temp;
  float min_temp;
  float max_temp;
  int humidity;
  float rain;
  int pressure;

  String weather1;
  String description1;
  String icon1;
  String dt_txt1;
  int id1;
  int windeg1;
  int cloud1;
  float windspeed1;
  int pressure1;
  int humidity1;
  float current_Temp1;
  float min_temp1;
  float max_temp1;
  float rain1;


  String weather2;
  String description2;
  String icon2;
  String dt_txt2;
  int id2;
  int windeg2;
  int cloud2;
  float windspeed2;
  int pressure2;
  int humidity2;
  float current_Temp2;
  float min_temp2;
  float max_temp2;
  float rain2;

  String weather3;
  String description3;
  String icon3;
  String dt_txt3;
  int id3;
  int windeg3;
  int cloud3;
  float windspeed3;
  int pressure3;
  int humidity3;
  float current_Temp3;
  float min_temp3;
  float max_temp3;
  float rain3;

  String weather4;
  String description4;
  String icon4;
  String dt_txt4;
  int id4;
  int windeg4;
  int cloud4;
  float windspeed4;
  int pressure4;
  int humidity4;
  float current_Temp4;
  float min_temp4;
  float max_temp4;
  float rain4;

  String weather5;
  String description5;
  String icon5;
  String dt_txt5;
  int id5;
  int windeg5;
  int cloud5;
  float windspeed5;
  int pressure5;
  int humidity5;
  float current_Temp5;
  float min_temp5;
  float max_temp5;
  float rain5;

  String weather6;
  String description6;
  String icon6;
  String dt_txt6;
  int id6;
  int windeg6;
  int cloud6;
  float windspeed6;
  int pressure6;
  int humidity6;
  float current_Temp6;
  float min_temp6;
  float max_temp6;
  float rain6;

  String weather7;
  String description7;
  String icon7;
  String dt_txt7;
  int id7;
  int windeg7;
  int cloud7;
  float windspeed7;
  int pressure7;
  int humidity7;
  float current_Temp7;
  float min_temp7;
  float max_temp7;
  float rain7;

    String weather8;
  String description8;
  String icon8;
  String dt_txt8;
  int id8;
  int windeg8;
  int cloud8;
  float windspeed8;
  int pressure8;
  int humidity8;
  float current_Temp8;
  float min_temp8;
  float max_temp8;
  float rain8;

    String weather9;
  String description9;
  String icon9;
  String dt_txt9;
  int id9;
  int windeg9;
  int cloud9;
  float windspeed9;
  int pressure9;
  int humidity9;
  float current_Temp9;
  float min_temp9;
  float max_temp9;
  float rain9;

    String weather10;
  String description10;
  String icon10;
  String dt_txt10;
  int id10;
  int windeg10;
  int cloud10;
  float windspeed10;
  int pressure10;
  int humidity10;
  float current_Temp10;
  float min_temp10;
  float max_temp10;
  float rain10;
};

class Weathercall
{
  public:
    Weathercall(String Key, String City); 
    Weathercall(String Key, float lat, float longi);
    Weathercall(String Key, String City, boolean forecast);
    Weathercall(String Key, String City, String forecast2);
    void updateStatus(weatherData *w);
    String getResponse();
  private:
    String _Response;
    String _url;
    boolean _forecast;
    String _forecast2;
};
#endif