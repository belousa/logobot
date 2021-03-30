
#include "Logo.h"
#include "Button.h"
#include "YawSource.h"
#include "YawDifference.h"

constexpr int buttonPin = 8;

Button button(8);
YawSource yawSource;

#include "Scheduler.h"


// The order is in Logo.h
constexpr const int leds[4] = {9,10,11,12};

class LogoLed {

  int desiredYaw = 0;
  
public:
  void setup() {
    button.setup();
    yawSource.setup();
    for (auto l : leds) {
      pinMode(l, OUTPUT);
    }
  }

public:
  void walk(Direction dir, int steps)
  {
    for (int i = 0; i < steps; i++) {
      walk(leds[dir]);
    }  
  }

  void turn(Direction dir, int rightAngles)
  {
    for (int i = 0; i < rightAngles; i++) {
      turn(dir);
    }  
  }

  void done() {
    digitalWrite(leds, 4, HIGH);
    while (true);
  }

  void bow() {
    beforeAction();
    blinkAllFast(600);
    completeAction();
  }

private:
  void beforeAction()
  {
    button.resetCounts();
  }

  void completeAction() {
    Scheduler::delayUntil([](){return button.pushedCount() > 0;});
  }
  

  void walk(int led) 
  {
    beforeAction();
    blinkFast(led, 500);
    glowSteady(led, 500);
    completeAction();
  }
  void turn(Direction dir) 
  {
    beforeAction();
    YawDifference diff(computeNewYaw(dir));

    do {
      auto yaw = yawSource.yaw();
      auto angle = diff.turnAngle(yaw);
      auto diff = abs(angle);

      Serial.print(desiredYaw);
      Serial.print('\t');
      Serial.print(yaw);
      Serial.print('\t');
      Serial.print(angle);
      Serial.print('\t');
      Serial.println(diff);
      
      if (diff < 5) {
        // We're within 5 degrees - good enough.
        break;
      }

      int sign = angle > 0 ? 1 : -1;
      
      int led = sign == YawSource::clockwiseSign ? leds[CLOCKWISE] : leds[COUNTER_CLOCKWISE];
      int blinkTime = 25;
      if (diff <30) {
        blinkTime = 50;
      }
      
      glowSteady(led, blinkTime);
      Scheduler::delay(blinkTime);
      
    } while (true);
    blinkFast(leds+2, 2, 300);
    completeAction();
  }

  static void digitalWrite(const int *leds, int size, int value) {
      for (int i = 0; i < size;i++) {
        ::digitalWrite(leds[i], value);
      }
  }

  void blinkFast(int led, int millis) {
    blinkFast(&led, 1, millis);
  }

  void blinkAllFast(int millis) {
    blinkFast(leds, 4, millis);
  }


  void blinkFast(const int *leds, int size, int millis)
  {
    static const int FAST = 60;
    while (millis > 0) {
      int timeToWait = min(millis, FAST);
      millis -= timeToWait;
      digitalWrite(leds, size, HIGH);
      Scheduler::delay(timeToWait);

      timeToWait = min(millis, FAST);
      millis -= timeToWait;
      digitalWrite(leds, size, LOW);
      Scheduler::delay(timeToWait);
    }
  }
  
  void glowSteady(int led, int millis)
  {
      ::digitalWrite(led, HIGH);
      Scheduler::delay(millis);
      ::digitalWrite(led, LOW);
  }

  float computeNewYaw(Direction dir) {
    auto incr = YawSource::clockwiseSign * 90;
    if (dir == CLOCKWISE) {
      desiredYaw += incr;
    } else {
      desiredYaw -= incr;
    }

    if (desiredYaw > 180) desiredYaw -= 360;
    if (desiredYaw < -180) desiredYaw += 360;

    return desiredYaw;
  }

};
