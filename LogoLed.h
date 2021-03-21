
#include "Logo.h"
#include "Button.h"

constexpr const int buttonPin = 8;

Button button(8);

#include "Scheduler.h"


// The order is in Logo.h
constexpr const int leds[4] = {9,10,11,12};

class LogoLed {
public:
  void setup() {
    button.setup();
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
      turn(leds[dir]);
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
  void turn(int led) 
  {
    beforeAction();
    blinkFast(led, 300);
    glowSteady(led, 500);
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
  
};
