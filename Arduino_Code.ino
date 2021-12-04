#include "HX711.h"

int Xreading = 0;
int Yreading = 0;
int Zreading = 0;

HX711 Xsensor;
HX711 Ysensor;
HX711 Zsensor;

unsigned long runCount = 0;

unsigned long Xsum = 0;
unsigned long Ysum = 0;
unsigned long Zsum = 0;

unsigned long Xavg = 0;
unsigned long Yavg = 0;
unsigned long Zavg = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Current time,X,Y,Z,Xavg,Yavg,Zavg");

  Xsensor.begin(2, 3);
  Ysensor.begin(4, 5);
  Zsensor.begin(6, 7);
}
void loop()
{
  if (Xsensor.is_ready() && Ysensor.is_ready() && Zsensor.is_ready()) 
  {
   Xreading = abs(Xsensor.read());
   Yreading = abs(Ysensor.read());
   Zreading = abs(Zsensor.read());
  }
  else
  {
   Xreading = 0;
   Yreading = 0;
   Zreading = 0;
  }
  
  Xsum = Xsum + Xreading;
  Ysum = Ysum + Yreading;
  Zsum = Zsum + Zreading;

  runCount = runCount + 1;
  
  Xavg = Xsum/runCount;
  Yavg = Ysum/runCount;
  Zavg = Zsum/runCount;
  
  Serial.print("DATA,TIME,");
  Serial.print(Xreading);
  Serial.print(",");
  Serial.print(Yreading);
  Serial.print(",");
  Serial.print(Zreading);
  Serial.print(",");
  Serial.print(Xavg);
  Serial.print(",");
  Serial.print(Yavg);
  Serial.print(",");
  Serial.println(Zavg);

  delay(100);
}


