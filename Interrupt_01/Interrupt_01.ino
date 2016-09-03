 void setup()
{
  Serial.begin(9600);

  //attachInterrupt(0, testISR_Rising, RISING);
  //attachInterrupt(0, testISR_Falling, FALLING);
  attachInterrupt(0, testISR, CHANGE);
}
 
void loop()
{
  delay(100);
}

void testISR_Rising()
{
  Serial.println("Hello");
}

void testISR_Falling()
{
  Serial.println("World!");
}

void testISR()
{
  static int state = 0;
  state = !state;

  if (state) {
    testISR_Rising();
  } else {
    testISR_Falling();
  }
}

