#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 5
#define RST_PIN 34
#define SERVO_PIN 33

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
LiquidCrystal_I2C lcd(0x27, 20, 4);
byte nuidPICC[4]; // Init array that will store new NUID 

void setup() { 
  lcd.begin();
  Serial.begin(115200);
  pinMode(SERVO_PIN, OUTPUT);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  // myservo.write(0);

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("Welcome To");
  lcd.setCursor(6, 1);
  lcd.print("Hashkunz");
  lcd.setCursor(3, 2);
  lcd.print("www.hashkun.com");
  lcd.setCursor(3, 3);
  lcd.print("H A S H K U N Z");
}
 
void loop() {
  delay(1000);
  Serial.println("Tap Card!!");
  lcd.clear();
  lcd.setCursor(2, 1); // ไปที่ตัวอักษรที่ 6 แถวที่ 2
  lcd.print("Tap Your Card!!");
  lcd.setCursor(7, 2); // ไปที่ตัวอักษรที่ 0 แถวที่ 1
  lcd.print("Here!");

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && 
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("Your Pass!!");
    lcd.setCursor(6, 2);
    lcd.print("Welcome!");

    Serial.println("-------------- servo working --------------");
    digitalWrite(SERVO_PIN, HIGH); // เปิดขาของ Servo
    delayMicroseconds(785);
    digitalWrite(SERVO_PIN, LOW); // ปิดขาของ Servo
    delayMicroseconds(1950);
    Serial.println("------------ servo stop working ------------");
  }

  else {
    Serial.println(F("Card read previously."));
    lcd.clear();
    lcd.setCursor(2, 1); // ไปที่ตัวอักษรที่ 6 แถวที่ 2
    lcd.print("ChangeYourCard!!");
    lcd.setCursor(2, 2); // ไปที่ตัวอักษรที่ 0 แถวที่ 1
    lcd.print("H A S H K U N Z");
    }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
