 #include <DHT11.h>
#include "pitches.h"
int speakerpin = 2; //스피커가 연결된 디지털핀 설정
int motorPin = 3;
int pin=4;
int lightPin = 5 ;
int light_v = 1;    //  LED를 켰다 껐다 할 수 있는 변수
DHT11 dht11(pin); 
char data[7] = {0,};
char message;
 
//음계 데이터 (24개)
int melody[] = {NOTE_G7,NOTE_G7,NOTE_A7,NOTE_A7,NOTE_G7,NOTE_G7,NOTE_E7,
                NOTE_G7,NOTE_G7,NOTE_E7,NOTE_E7,NOTE_D7,
                NOTE_G7,NOTE_G7,NOTE_A7,NOTE_A7,NOTE_G7,NOTE_G7,NOTE_E7,
                NOTE_G7,NOTE_E7,NOTE_D7,NOTE_E7,NOTE_C7};
//음의길이, 4:4분음표, 2:2분음표
int noteDurations[] = {4,4,4,4,4,4,2,4,4,4,4,1,4,4,4,4,4,4,2,4,4,4,4,1};  //  스피커

void setup()
{
   pinMode(motorPin, OUTPUT); //  진동 모터핀
   pinMode(lightPin, OUTPUT);
   digitalWrite(lightPin, HIGH);
   Serial.begin(9600);
   Serial1.begin(9600); //블루투스 시리얼
  while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
}

void loop()
{
  int err;
  float temp, humi;
  
  if((err=dht11.read(humi, temp))==0)
  {
    
    int a = temp;
    int b = humi;
    sprintf(data,"%03d%03d",a,b);
    //bluetooth.print(data);
    Serial.print(data);
    Serial1.print(data);

  }
  else
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }
  delay(500); //delay for reread
  

  if(Serial1.available()){
    message = Serial1.read();
    Serial.println(message);
    delay(1);

    
    if(message == 'v'){
       digitalWrite(motorPin, HIGH);
       delay(1000);
       digitalWrite(motorPin, LOW);
    }
    
    if(message == 'b'){
      for (int thisNote = 0; thisNote < 24; thisNote++)
      {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(speakerpin, melody[thisNote], noteDuration); //소리를 낸다.
        int pauseBetweenNotes = noteDuration * 1.30;      //delay 계산식
        delay(pauseBetweenNotes);                         //delay
        noTone(speakerpin);                               //대상핀 출력 중단
      }
    }
    
    if(message == 't'){
      if( light_v == 1 ){
        digitalWrite(lightPin, LOW);
        delay(100);
        light_v = 0;
        }
        else if( light_v == 0 ){
          digitalWrite(lightPin, HIGH);
          delay(100);
          light_v = 1;
        }
    }
  }
}



