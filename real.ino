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


unsigned long myChannelNumber = 2024737;
const char * myWriteAPIKey = "0QVO0MKQ0TEZ7AY7";


int S1 = 34, H1; //
int S2 = 35, H2; //
int S3 = 32, H3; //
int S4 = 33, H4; //


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



  float humd = sht20.readHumidity(); // Read Humidity
  float temp = sht20.readTemperature(); // Read Temperature

  H1 = analogRead(S1);
  Serial.println(String("Default Humi1 : ") + H1);
  Serial.print("Temperature :");
  Serial.print(temp, 1);
  Serial.print("C");
  Serial.print("  Humid :");
  Serial.print(humd, 1);
  Serial.print("%");
  Serial.println();

  H2 = analogRead(S2);
  Serial.println(String("Default Humi2 : ") + H2);
  Serial.print("Temperature :");
  Serial.print(temp, 1);
  Serial.print("C");
  Serial.print("  Humid :");
  Serial.print(humd, 1);
  Serial.print("%");
  Serial.println();

  H3 = analogRead(S3);
  Serial.println(String("Default Humi3 : ") + H3);
  Serial.print("Temperature :");
  Serial.print(temp, 1);
  Serial.print("C");
  Serial.print("   Humid :");
  Serial.print(humd, 1);
  Serial.print("%");
  Serial.println();

  H4 = analogRead(S4);
  Serial.println(String("Default Humi4 : ") + H4);
  Serial.print("Temperature :");
  Serial.print(temp, 1);
  Serial.print("C");
  Serial.print("  Humid :");
  Serial.print(humd, 1);
  Serial.print("%");
  Serial.println();

ThingSpeak.setField(1, H1);
ThingSpeak.setField(2, H2); 
ThingSpeak.setField(3, H3);
ThingSpeak.setField(4, H4);
ThingSpeak.setField(5, temp); //อุณหภูมิ
ThingSpeak.setField(6, humd); //ความชื้น
// ThingSpeak.setField(7, 0);
// ThingSpeak.setField(8, 0);


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
      res = wm.autoConnect("ตู้ Stawberry v.1","12345678"); // password protected ap
    if(!res) {
        Serial.println("Failed to connect");     
    } 
    else {
             Serial.println("connected...yeey :)");
    }
}
