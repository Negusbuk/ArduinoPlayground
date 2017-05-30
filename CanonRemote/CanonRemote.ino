#include <avr/wdt.h>
#include <Wire.h>

int focusPin = 6;
int triggerPin = 7;
int statusLED = 13;

int statusCounter = 0;

byte lastAddress = 0;

uint16_t exposureTime = 0x0010;
bool exposureLoopActive = false;
bool inExposure = false;
unsigned long timeAtExposureStart;
unsigned long timeAtExposureEnd;

void setup()
{
  // join I2C bus with address 0x08
  Wire.begin(0x08);
  // register handler function when data is received
  Wire.onReceive(receiveEvent);
  // register handler function when data is requested
  Wire.onRequest(requestEvent);

  // initialize the digital pin as an output.
  pinMode(focusPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(statusLED, OUTPUT);
}

void focusON()
{
  triggerOFF();
  digitalWrite(focusPin, HIGH);
}

void focusOFF()
{
  digitalWrite(focusPin, LOW);
}

void triggerON()
{
  focusOFF();
  digitalWrite(triggerPin, HIGH);
}

void triggerOFF()
{
  digitalWrite(triggerPin, LOW);
}

void loop()
{
  statusCounter++;

  if (statusCounter == 40) {
    digitalWrite(statusLED, HIGH);
    delay(50);
    digitalWrite(statusLED, LOW);
    statusCounter = 0;
  }

  if (!inExposure) {
    if (exposureLoopActive) {
      timeAtExposureStart = millis();
      timeAtExposureEnd = timeAtExposureStart + exposureTime * 100;
      inExposure = true;
      triggerON();
    }
  } else {
    if (millis() > timeAtExposureEnd) {
      inExposure = false;
      triggerOFF();
      delay(500);
    }
  }

  delay(100);
}

// Restarts program from beginning but does not reset the peripherals and registers
void _SoftwareReset()
{
  wdt_enable(WDTO_15MS);
}

// function that executes whenever data is received from master
void requestEvent()
{
  if (lastAddress == 0x10) {
    byte buffer[2];
    buffer[1] = exposureTime >> 8;
    buffer[0] = exposureTime & 0xff;
    Wire.write(buffer, 2);
  }

  lastAddress = 0;
}

// function that executes whenever data is received from master
void receiveEvent(int arg)
{
  byte data0;
  byte data1;

  // receive bytes from i2c bus
  if (Wire.available() > 0) {
    // read the register address being written to
    lastAddress  = Wire.read();

    // handle received commands and data
    if (Wire.available() > 0) {
      data0 = Wire.read();

      // the reset
      if (lastAddress == 0xde && data0 == 0xad) {
        _SoftwareReset();
      }

      if (lastAddress == 0x10) {
        data1 = 0x00;
        if (Wire.available() > 0) {
          data1 = Wire.read();
        }
        exposureTime = data1 << 8 | data0;

        lastAddress = 0;
      }

      if (lastAddress == 0x11 && data0 == 0x00) {
        exposureLoopActive = false;
      }
      if (lastAddress == 0x11 && data0 == 0x01) {
        exposureLoopActive = true;
      }

      if (lastAddress == 0x12 && data0 == 0x00) {
        focusOFF();
      }

      if (lastAddress == 0x12 && data0 == 0x01) {
        focusON();
      }

      if (lastAddress == 0x13 && data0 == 0x00) {
        triggerOFF();
      }

      if (lastAddress == 0x13 && data0 == 0x01) {
        triggerON();
      }
    }
  }
}
