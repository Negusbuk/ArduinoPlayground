#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
static const unsigned long data = 0x2468ACEB;
static char temp[9];

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  mySwitch.enableTransmit(10);
}

void loop()
{
  mySwitch.send(data, 32);
  Serial.print("Sent 0x");
  sprintf(temp, "%08lX", data);
  Serial.println(temp);
      
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  
  delay(2000);
}

