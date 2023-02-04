int S1 = 34, H1; //
int S2 = 35, H2; //
int S3 = 32, H3; //
int S4 = 33, H4; //
int S5 = 25, H5; //

void setup() {
  Serial.begin(115200);
  Serial.println("Serial begin");
  delay(2000);
}

void loop() {
  H1 = analogRead(S1);
  Serial.println(String("Default Analog1 : ") + H1);
  H1 = map(H1, 3000, 1330, 0,100);
  Serial.println(String(" Value after mapped1 : ") + H1);
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
  delay(3000);
}
