#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
char temp[9];
static const char sizeOfULong = 8 * sizeof(unsigned long);
  
void sendBit(bool bit)
{
  digitalWrite(9, bit);
  delay(10);
  digitalWrite(8, HIGH);
  delay(10);
  digitalWrite(8, LOW);
}

void sendValue(unsigned long value)
{
  Serial.print("sendValue(0x");
  sprintf(temp, "%08lX", value);
  Serial.print(temp);
  Serial.println(")");
  for (int b = 0;b<sizeOfULong;++b) {
    sendBit(value & 0x00000001);
    value >>= 1;
  }
}

void setup()
{
  Serial.begin(9600);
  mySwitch.enableReceive(0);

  pinMode(8, OUTPUT); // serial clock
  pinMode(9, OUTPUT); // serial data
}

void loop()
{
  static unsigned long oldValue = 0;
  static unsigned long nextTime = 0;
   
  if (mySwitch.available()) {
    
    unsigned long value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {

      if (value!=oldValue) {
        oldValue = value;
        nextTime = millis() + 2000;
      }
      
      Serial.print("Received 0x");
      sprintf(temp, "%08lX", mySwitch.getReceivedValue());
      Serial.print(temp);
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
    }

    mySwitch.resetAvailable();
  }

  if (millis()>nextTime) {
    nextTime = 0xFFFFFFFF;
    oldValue = 0;
    sendValue(random());
  }

  delay(100);
}
