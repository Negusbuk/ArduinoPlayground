#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
char temp[9];

void setup()
{
  Serial.begin(9600);
  mySwitch.enableReceive(0);
}

void loop()
{
  if (mySwitch.available()) {
    
    unsigned long value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
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
}
