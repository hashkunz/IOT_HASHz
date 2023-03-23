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

unsigned long myChannelNumber = Channel ID; //Input Your ChannelID Number
const char * myWriteAPIKey = "API Key"; //Input Your API_Key ThinkSpeak

int S1 = 33, H1; //SenSor1
int S2 = 32, H2; //SenSor2
int S3 = 34, H3; //SenSor3
int S4 = 36, H4; //SenSor4
int S5 = 39, H5; //SenSor5

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
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
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
  H1 = map(H1, 4095, 1750, 0,100);
  Serial.println(String("Default Humi1 : ") + H1);
  // Serial.print("Temperature :");
  // Serial.print(temp, 1);
  // Serial.print("C");
  // Serial.print("Humid :");
  // Serial.print(humd, 1);
  // Serial.print("%");
  Serial.println();

 H2 = analogRead(S2);
  H2 = map(H2, 900, 500, 0,100);
  Serial.println(String("Default Humi2 : ") + H2);
  Serial.println();

   H3 = analogRead(S3);
  H3 = map(H3, 3000, 1100, 0,100);
  Serial.println(String("Default Humi3 : ") + H3);
  Serial.println();

   H4 = analogRead(S4);
  H4 = map(H4, 3000, 1500, 0,100);
  Serial.println(String("Default Humi4 : ") + H4);
  Serial.println();

   H5 = analogRead(S5);
  H5 = map(H5, 3000, 1500, 0,100);
  Serial.println(String("Default Humi5 : ") + H5);
  Serial.println();

  ThingSpeak.setField(1, H1);
  ThingSpeak.setField(2, H2); 
  ThingSpeak.setField(3, H3);
  ThingSpeak.setField(4, H4);
  ThingSpeak.setField(5, H5); 
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
      Serial.println("connected...🙂 ");
    }
}
