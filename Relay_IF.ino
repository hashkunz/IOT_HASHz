int sensor = 34, Hash;  //pin read data
int R1 = 25; //
int R2 = 26; //
int L1 = 18; //
int L2 = 19; //

void setup() {
  Serial.begin(115200);
  Serial.println("Serial begin");
  delay(2000);
  pinMode(R1, OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(L1,OUTPUT);  
  pinMode(L2,OUTPUT);  
  digitalWrite(L1,HIGH);
  digitalWrite(L2,HIGH);
}

void loop() {
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  Hash = analogRead(sensor);
  Serial.println(String("Default Analog : ") + Hash);
  Hash = map(Hash, 3000, 1330, 0,100);
  Serial.println(String(" Value after mapped : ") + Hash);
  if (Hash >= 80){
    digitalWrite(R1, LOW);
    Serial.println("Enough water for plant");
  }
  else if (Hash <= 40){
    digitalWrite(R2, LOW);
    Serial.println("water level is low");
  }
  else {
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
    Serial.println("Water level is OK");
  }
  delay(2000);
}
