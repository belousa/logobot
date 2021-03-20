
#include "LogoLed.h"

LogoLed logo;

void setup() {
  logo.setup();
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
  fwd();
  bow();
  counter(2);
  back(2);
  counter();
  fwd(2);
  counter();
  bow();
  
  done();
}
