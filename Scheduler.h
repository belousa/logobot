
struct Scheduler {
  static void delay(int ms) {
    ::delay(ms);
  }

  static void yield() {
    auto ms = millis();
    yawSource.update(ms);
  }

  template <class F, class ...ARGS>
  static void delayUntil(F f,  ARGS... args) {
    while (!f(args...)) {
      yield();
    }
  }
};
