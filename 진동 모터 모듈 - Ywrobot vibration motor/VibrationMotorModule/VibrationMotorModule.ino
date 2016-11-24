// Code to vibrate the motor every minute
 const int motorPin = 37;

 void setup()
 {
 pinMode(motorPin, OUTPUT);
 }

 void loop()
 {
 digitalWrite(motorPin, HIGH);
 delay(1000);
 digitalWrite(motorPin, LOW);
 delay(59000);
 }

