// Based on http://www.ganssle.com/debouncing-pt2.htm

constexpr int CHECK_MSEC = 5;
constexpr int PRESS_MSEC = 10;
constexpr int RELEASE_MSEC = 50;


class Button {
  unsigned long d_nextCheckTime = 0;
  bool d_isPressed = false;
  char d_counter = releaseCounter();
  const char d_pin;
  
  unsigned char d_pushedCount;
  // Number of times the button has been pushed down since last resetCounts()

  unsigned char d_poppedCount;
  // Number of times the button has been popped up since last resetCounts()

public:
  Button(char pin) : d_pin(pin) {}

public:
  void setup() {
    pinMode(d_pin, INPUT);
  }

public:
  void update(unsigned long ms) {
    if (ms >= d_nextCheckTime) {
      d_nextCheckTime = ms + CHECK_MSEC;
      debounce();
    }
  }


public:
     unsigned char pushedCount() {return d_pushedCount;}
     unsigned char poppedCount() {return d_poppedCount;}
     void resetCounts() {d_pushedCount = 0; d_poppedCount = 0;}
 private:

  void debounce() {
    bool buttonReportsAsPressed = (digitalRead(d_pin) == HIGH);

    if (buttonReportsAsPressed == d_isPressed) {
      // Set the counter that will eventually allow the state change
      d_counter = d_isPressed ? releaseCounter() : pressCounter();
    } else {
      if (--d_counter == 0) {
        // the state has been stable for a number of iteartions - accept it
        d_isPressed = buttonReportsAsPressed;
        if (d_isPressed) ++d_pushedCount;
        else ++d_poppedCount;
        d_counter = d_isPressed ? releaseCounter() : pressCounter();
      }
    }  
  }
private:
  constexpr char releaseCounter() {
    return RELEASE_MSEC / CHECK_MSEC;
  }    
  constexpr char pressCounter() {
    return PRESS_MSEC / CHECK_MSEC;
  }    
};
