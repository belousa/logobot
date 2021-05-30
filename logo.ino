#include <Wire.h>

#include "LogoMotor.h"

LogoMotor logo;

void setup()
{

  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
  Wire.setClock(100000);

  // initialize serial communication
  // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
  // it's really up to you depending on your project)
  Serial.begin(115200);

  Serial.println(F("Setup called first"));

  logo.setup();
  pinMode(13, OUTPUT);
}

void fwd(int steps = 1)
{
  logo.walk(FWD, steps);
}

void back(int steps = 1)
{
  logo.walk(BACK, steps);
}

void clockw(int rightAngles = 1)
{
  logo.turn(CLOCKWISE, rightAngles);
}

void counter(int rightAngles = 1)
{
  logo.turn(COUNTER_CLOCKWISE, rightAngles);
}

void bow()
{
  logo.bow();
}

void done()
{
  while (true)
  {
  }
}

// the loop function runs over and over again forever
void loop()
{
  clockw(2);
  fwd();
  counter(2);
  fwd();
}

#include "hooks.h"
