
struct Scheduler {
  static void delay(int ms) {
    ::delay(ms);
  }

  static void yield() {
    auto ms = millis();
    button.update(ms);
  }

  template <class F, class ARG>
  static void delayUntil(F f,  ARG *arg) {
    while (!f(arg)) {
      yield();
    }
  }
};
