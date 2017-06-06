#include <avr/wdt.h>
#include <Wire.h>

int focusPin = 6;
int triggerPin = 7;
int statusLED = 13;

int statusCounter = 0;

byte lastAddress = 0;

uint16_t exposureTime = 5; // [seconds]
uint16_t dt;

bool exposureLoopActive = false;
bool focusOn = false;
bool triggerOn = false;
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
  triggerOn = false;
  focusOn = true;
  triggerOFF();
  digitalWrite(focusPin, HIGH);
}

void focusOFF()
{
  focusOn = false;
  digitalWrite(focusPin, LOW);
}

void triggerON()
{
  triggerOn = true;
  focusOn = false;
  focusOFF();
  digitalWrite(triggerPin, HIGH);
}

void triggerOFF()
{
  triggerOn = false;
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

  unsigned long timeStamp = millis();
 
  dt = 0;
  
  if (!inExposure) {
    if (exposureLoopActive) {
      timeAtExposureStart = timeStamp;
      unsigned long milliExposureTime = exposureTime;
      timeAtExposureEnd = timeAtExposureStart + milliExposureTime * 1000;
      inExposure = true;
      triggerON();
    }
  } else {
    if (timeStamp >= timeAtExposureEnd) {
      inExposure = false;
      triggerOFF();
      delay(500);
    } else {
      dt = double(timeAtExposureEnd - timeStamp)/1000.;
    }
  }
  
  delay(100);
}

void _SoftwareReset()
{
  wdt_enable(WDTO_15MS);
}

void requestEvent()
{
  if (lastAddress == 0x10) {
    Wire.write((uint8_t*)&exposureTime, 2);
  }
  if (lastAddress == 0x11) {
    Wire.write((uint8_t)exposureLoopActive);
  }
  if (lastAddress == 0x12) {
    Wire.write((uint8_t)focusOn);
  }
  if (lastAddress == 0x13) {
    Wire.write((uint8_t)triggerOn);
  }
  if (lastAddress == 0x20) {
    uint8_t data = exposureTime >> 8;
    Wire.write(data);
  }
  if (lastAddress == 0x21) {
    uint8_t data = exposureTime & 0xff;
    Wire.write(data);
  }
  if (lastAddress == 0x30) {
    uint8_t data = dt >> 8;
    Wire.write(data);
  }
  if (lastAddress == 0x31) {
    uint8_t data = dt & 0xff;
    Wire.write(data);
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
      }

      if (lastAddress == 0x11 && data0 == 0x00) {
        exposureLoopActive = false;
      }
      if (lastAddress == 0x11 && data0 == 0x01) {
        focusOFF;
        triggerOFF;
        exposureLoopActive = true;
      }

      if (lastAddress == 0x12 && data0 == 0x00) {
        if (!exposureLoopActive) focusOFF();
      }

      if (lastAddress == 0x12 && data0 == 0x01) {
        if (!exposureLoopActive) focusON();
      }

      if (lastAddress == 0x13 && data0 == 0x00) {
        if (!exposureLoopActive) triggerOFF();
      }

      if (lastAddress == 0x13 && data0 == 0x01) {
        if (!exposureLoopActive) triggerON();
      }
    }
  }
}
