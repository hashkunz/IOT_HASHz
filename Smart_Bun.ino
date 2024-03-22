#include <TridentTD_LineNotify.h>
#include <WiFiManager.h> 
#include "ThingSpeak.h" 
#include <NTPClient.h>
#include <WiFiUdp.h>
#define LINE_TOKEN  "Your Token"

WiFiClient  client;
WiFiUDP ntpUDP;

// หน่วยเป็นวินาที จะได้ 7*60*60 = 25200
const long offsetTime = 25200; 
NTPClient timeClient(ntpUDP, "pool.ntp.org", offsetTime);

unsigned long myChannelNumber = your number; //Input Your ChannelID Number
const char * myWriteAPIKey = "your api"; //Input Your write API_Key ThinkSpeak

String myStatus = "";
String weekDay = "";
int hour;
int minute;
int second;
int count = 0;
bool set = true;
String weekDays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int detectorPin = 34;
int val; 
int detectorPin1 = 33;
int val1; 
int buzzer = 25;

void setup() {
  Serial.begin(115200); Serial.println();
  setupWiFi();
  Serial.println(LINE.getVersion());
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  timeClient.begin();
  LINE.setToken(LINE_TOKEN);
  pinMode(detectorPin, INPUT);
  pinMode(detectorPin1, INPUT);
  pinMode(buzzer, OUTPUT);

  Serial.println(F("Time Begin : "));
  Serial.println(timeClient.getFormattedTime());
  delay(3000);
  LINE.notify("เชื่อมต่อ WIFI สำเร็จแล้วระบบพร้อมทำงาน");
  LINE.notifyPicture("By Mulberry AI X WU", "https://img5.pic.in.th/file/secure-sv1/236845217_366300081776055_1001657747463195739_n.png");
}

void loop() {
    digitalWrite(buzzer, HIGH);
    timeClient.update();
    weekDay = weekDays[timeClient.getDay()];
    Serial.print("Week Day : ");
    Serial.println(weekDay);
    hour = timeClient.getHours();
    minute = timeClient.getMinutes();
    second = timeClient.getSeconds();
    Serial.printf("Time : %d : %d : %d \n", hour, minute, second);
    val = digitalRead(detectorPin);
    val1 = digitalRead(detectorPin1);
    Serial.printf("This Value : %d\n", val);
    Serial.printf("This Value : %d\n", val1);
    sendLineNotify(val, val1);
    delay(10000);
}

void sendLineNotify(int val, int val1) {
  String messageT = weekDay + ":  The garbage bin is not yet full.";
  String messageF = weekDay + ":  Bin full of garbage.";
  String error = "Read ERROR Please Check Your Sensor";
  if (val == 1 && val1 == 1) {
      LINE.notify(messageT);
      LINE.notifyPicture("Low Garbage", "https://img2.pic.in.th/pic/1572d97c4750fcf8c.png");
      sendThink(val, val1);
  } else if (val == 0 && val1 == 1) {
      LINE.notify(messageT);
      LINE.notifyPicture("Mediem Garbage", "https://img2.pic.in.th/pic/Smart-Bin-1.png");
      sendThink(val, val1);
  } else if ((val == 0 && val1 == 0)) {
      Serial.println("_____________");  
      Serial.println(" ");  
      Serial.println("   Full Now  ");  
      Serial.println("_____________");  
      digitalWrite(buzzer, LOW);
      delay(500);
      digitalWrite(buzzer, HIGH);
      LINE.notify(messageF);
      LINE.notifyPicture("Max Garbage", "https://img5.pic.in.th/file/secure-sv1/3e5f3433d8deb1a7a.png");
      sendThink(val, val1);
  } else {
    LINE.notify(messageF);
    LINE.notifyPicture("Error! ", "https://img5.pic.in.th/file/secure-sv1/Smart-Bin.png");
    sendThink(val, val1);
  }
}

void sendThink(int val, int val1) {
  ThingSpeak.setField(1, val1);
  ThingSpeak.setField(2, val);
  ThingSpeak.setStatus(myStatus);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Channel update successful.");
  }
  else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}


void setupWiFi() {
    WiFiManager wm;
    bool res;
    res = wm.autoConnect("Smart_Bin", "12345678");
    if (!res) {
      Serial.println("Failed to connect");     
    } 
    else {
      Serial.println("connected...:)");
    }
}
  
