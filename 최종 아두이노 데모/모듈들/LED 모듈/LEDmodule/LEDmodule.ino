const int lightpin = 5 ;

void setup() {
  pinMode(lightpin, OUTPUT);
  digitalWrite(lightpin, HIGH);

}

void loop() {
 digitalWrite(lightpin, HIGH);
 delay(100);
 digitalWrite(lightpin, LOW);
 delay(100);
}
