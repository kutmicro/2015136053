#include <math.h>
int a;
float temperature;
int B = 3975;                //B value of the thermistor
float resistance;

int ad_conv(byte channel, byte num);
int calc_RH10(int adval);


void setup() {
  Serial.begin(9600);
  starttime = millis();        //get the current time;
}


void loop() {
  {

      a = analogRead(A1);
      resistance = (float)(1023 - a) * 10000 / a; //get the resistance of the sensor;
      temperature = 1 / (log(resistance / 10000) / B + 1 / 298.15) - 273.15; //convert to temperature via datasheet ;
      Serial.print("                 ");
      Serial.print(temperature);
      Serial.print("           ");

      int adval, RH10;
      adval = ad_conv(0, 32); // 32 samples on Channel 0
      RH10 = calc_RH10(adval);
      display(RH10);
      Serial.println("");
      starttime = millis();
    }
  }
}



int ad_conv(byte channel, byte num)
{
  long sum = 0;
  byte n;

  for (n = 0; n < num; n++)
  {
    sum = sum + analogRead(channel);
  }
  return (sum / num);
}


int calc_RH10(int adval)
{
  int RH10;
  RH10 = adval + 6 * adval / 10 + 3 * adval / 100; // 1.63 * adval
  return (RH10);
}


void display(int x)
{
  int whole, fract;

  whole = x / 10;
  fract = x % 10;

  Serial.print(whole, DEC);
  Serial.print(".");
  Serial.print(fract, DEC);

}

