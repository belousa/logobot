
#include "LogoLed.h"

LogoLed logo;

void setup() {

  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
  Wire.setClock(400000);

  // initialize serial communication
  // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
  // it's really up to you depending on your project)
  Serial.begin(115200);

  
  logo.setup();
  pinMode(13, OUTPUT);
}


void fwd(int steps = 1)
{
  logo.walk(FORWARD, steps);
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

void done() {
  logo.done();
}

// the loop function runs over and over again forever
void loop() {
  //fwd();
  bow();
  counter(2);
  //back(2);
  clockw();
  //fwd(2);
  counter();
  //bow();
  //done();
}

#include "hooks.h"
