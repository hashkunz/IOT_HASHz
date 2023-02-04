#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

int S1 = 36, H1; //
int S2 = 39, H2; //
int S3 = 34, H3; //
int S4 = 35, H4; //
int S5 = 32, H5; //
int sensor = 15, val;

void setup() {
  Serial.begin(115200);
  Serial.println("Serial begin");
  Serial.println(F("DHTxx test!"));
  dht.begin();
  delay(2000);
}

void loop() {
  H1 = analogRead(S1);
  Serial.println(String("Default Analog1 : ") + H1);
  H1 = map(H1, 3000, 1330, 0,100);
  Serial.println(String(" Value after mapped1 : ") + H1);
  val = analogRead(sensor);
  Serial.println(val); 
  delay(3000);
  H2 = analogRead(S2);
  Serial.println(String("Default Analog2 : ") + H2);
  H2 = map(H2, 3000, 1330, 0,100);
  Serial.println(String(" Value after mapped2 : ") + H2);
  delay(3000);
  H3 = analogRead(S3);
  Serial.println(String("Default Analog3 : ") + H3);
  H3 = map(H3, 3000, 1330, 0,100);
  Serial.println(String(" Value after mapped3 : ") + H3);
  delay(3000);
  H4 = analogRead(S4);
  Serial.println(String("Default Analog4 : ") + H4);
  H4 = map(H4, 3000, 1330, 0,100);
  Serial.println(String(" Value after mapped4 : ") + H4);
  delay(3000);
  H5 = analogRead(S5);
  Serial.println(String("Default Analog5 : ") + H5);
  H5 = map(H5, 3000, 1330, 0,100);
  Serial.println(String(" Value after mapped5 : ") + H5);
  val = analogRead(sensor);
  Serial.println(val);
  delay(3000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F(" C "));
  Serial.print(f);
  Serial.print(F(" F  Heat index: "));
  Serial.print(hic);
  Serial.print(F(" C "));
  Serial.print(hif);
  Serial.println(F(" F"));
}
