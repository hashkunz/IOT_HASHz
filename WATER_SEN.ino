int sensor = A0;
int val = 0;

void setup() { 
  Serial.begin(9600); 
}   

void loop() { 
  val = analogRead(sensor);
  Serial.println(val); 
  delay(2000);
  // if (val > 1000){
  // }
  // else {
  // }
  // delay(100);
}
