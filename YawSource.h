
#include "MPU6050_6Axis_MotionApps20.h"


class YawSource
{
private:
  MPU6050 mpu;
  bool isReady = false;
  float currentYaw = 0;
  unsigned long lastCheck = 0;

public:

  void setup() {
    if (!mpu.testConnection()) {
      // TODO: do some blinking
      return;
    }

    if (0 != mpu.dmpInitialize()) {
      // TODO: do some blinking
      Serial.println(F("Yaw Initialization Failed"));
      return;     
    }
    
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.setDMPEnabled(true);
    Serial.println(F("Yaw Initializated"));
    isReady = true;
  }
  
  void update(unsigned long ms) {
    if (!isReady) return;
    if (lastCheck == ms) return;
    lastCheck = ms;

    uint8_t fifoBuffer[64];

    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
 
      Quaternion q;           // [w, x, y, z]         quaternion container
      VectorFloat gravity;    // [x, y, z]            gravity vector
      float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

      currentYaw = ypr[0];
    }
  }

  int yaw() {
    return (int)(currentYaw  * 180/M_PI + 0.5); 
  }

  constexpr static int clockwiseSign = -1;
};
