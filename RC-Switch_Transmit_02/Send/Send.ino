#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
static const unsigned long data = 0x2468ACEB;
static char temp[9];

void setup()
{
  Serial.begin(9600);
  attachInterrupt(0, remoteClock, RISING);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
  mySwitch.enableTransmit(10);
}

void loop()
{
  delay(1000);
}

void remoteClock()
{
  static unsigned long bitBuffer;
  static char bitCount = 0;

  bool bit = digitalRead(3);
  if (bit) {
    unsigned long temp = 0x1;
    temp <<= bitCount;
    bitBuffer |= temp;
  }
  //Serial.print(bit);
  //Serial.println(" clock");

  ++bitCount;
  if (bitCount==32) {
    Serial.print("received value 0x");
    sprintf(temp, "%08lX", bitBuffer);
    Serial.println(temp);

    delay(100);
    mySwitch.send(bitBuffer, 32);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);

    bitBuffer = 0;
    bitCount = 0;
  }
}

