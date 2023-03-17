#include "DFRobot_SHT20.h"
#include <WiFiManager.h> 
#include "ThingSpeak.h" 
#include <NTPClient.h>
#include <WiFiUdp.h>

DFRobot_SHT20 sht20;
WiFiClient  client;
WiFiUDP ntpUDP;

const long offsetTime = 25200; 
NTPClient timeClient(ntpUDP, "pool.ntp.org", offsetTime);

unsigned long myChannelNumber = 2067578; //Input Your ChannelID Number
const char * myWriteAPIKey = "G2EDQ8T9MKEBT6KY"; //Input Your API_Key ThinkSpeak

int S1 = A0, H1; //SenSor1
int S2 = D2, H2; //SenSor2
// int S3 = 32, H3; //SenSor3
// int S4 = 33, H4; //SenSor4
// int S5 = 34, H5; //SenSor5
// int S6 = 35, H6; //SenSor6

String myStatus = "";
int year;
int month;
int day;
int hour;
int minute;
int second;
int count =0;
bool set = false;
// หน่วยเป็นวินาที จะได้ 7*60*60 = 25200

void setup() {
  Serial.begin(115200);
  setupWiFi();
  Serial.println("Serial begin");
  Serial.println("SHT20 Example!");
  sht20.initSHT20();
  delay(100);
  sht20.checkSHT20();

// Set delay between sensor readings based on sensor details.
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  timeClient.begin();
  timeClient.update();
  hour = timeClient.getHours();
  minute = timeClient.getMinutes();
  second = timeClient.getSeconds();
  Serial.println(F("Time Begin : "));
  Serial.println(timeClient.getFormattedTime());
  delay(5000);
}

void loop() {
  timeClient.update();
  Serial.print(F("Count : "));
  Serial.println(count);
    if(count > 9){
      count =0 ;
      set = true;
    }
  hour = timeClient.getHours();
  minute = timeClient.getMinutes();
  second = timeClient.getSeconds();
  Serial.println(F("Time Begin : "));
  Serial.println(timeClient.getFormattedTime());

  H1 = analogRead(S1);
  Serial.println(String("Default Humi1 : ") + H1);
  // Serial.print("Temperature :");
  // Serial.print(temp, 1);
  // Serial.print("C");
  // Serial.print("  Humid :");
  // Serial.print(humd, 1);
  // Serial.print("%");
  Serial.println();

  H2 = digitalRead(S2);
  Serial.println(String("Default Humi2 : ") + H2);
  Serial.println();

  // H3 = analogRead(S3);
  // Serial.println(String("Default Humi3 : ") + H3);
  // Serial.println();

  // H4 = analogRead(S4);
  // Serial.println(String("Default Humi4 : ") + H4);
  // Serial.println();

  // H5 = analogRead(S5);
  // Serial.println(String("Default Humi5 : ") + H5);
  // Serial.println();
  
  // H6 = analogRead(S6);
  // Serial.println(String("Default Humi6 : ") + H6);
  // Serial.println();

  ThingSpeak.setField(1, H1);
  ThingSpeak.setField(2, H2); 
  // ThingSpeak.setField(3, H3);
  // ThingSpeak.setField(4, H4);
  // ThingSpeak.setField(5, H5); 
  // ThingSpeak.setField(6, H6); 
  // ThingSpeak.setField(7, H7);
  // ThingSpeak.setField(8, H8);
  delay(15000);
  ThingSpeak.setStatus(myStatus);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}
  
void setupWiFi() {
    WiFiManager wm;
    bool res;
    res = wm.autoConnect("Left_SS","12345678"); // password protected ap
    if(!res) {
      Serial.println("Failed to connect");     
    } 
    else {
      Serial.println("connected...:) ");
    }
}
