#include <Arduino.h>

#include <Adafruit_MotorShield.h>

#include "YawSource.h"
#include "YawDifference.h"
#include "Chassis.h"

#include "Logo.h"

YawSource yawSource;

#include "Scheduler.h"

class LogoMotor
{
    int desiredYaw = 0;
    Chassis chassis;

public:
    void setup()
    {
        yawSource.setup();
        chassis.begin();
    }

public:
    void walk(Direction dir, int steps)
    {
        for (int i = 0; i < steps; i++)
        {
            walk(dir);
        }
    }

    void turn(Direction dir, int rightAngles)
    {
        for (int i = 0; i < rightAngles; i++)
        {
            turn(dir);
        }
    }

    void bow()
    {
    }

private:
    void walk(Direction dir)
    {
        if (dir == FWD)
        {
            chassis.forward(Speed::FAST);
        }
        else
        {
            chassis.back(Speed::FAST);
        }

        delay(1000);

        chassis.stop();

        delay(300);
    }

    void turn(Direction dir)
    {
        YawDifference diff(computeNewYaw(dir));

        do
        {
            yield();
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

            if (diff == 0)
            {
                // turn complete
                break;
            }

            int sign = (angle > 0 ? 1 : -1);

            bool shouldTurnClockwise = (sign == YawSource::clockwiseSign);

            auto speed = Speed::FAST;
            if (diff <= 30)
            {
                if (diff <= 10)
                {
                    speed = Speed::SLOW;
                }
                else
                {
                    speed = Speed::SLOWER;
                }
            }

            if (shouldTurnClockwise)
            {
                chassis.clockwise(speed);
            }
            else
            {
                chassis.counterclockwise(speed);
            }

        } while (true);
    }

    int computeNewYaw(Direction dir)
    {
        auto incr = YawSource::clockwiseSign * 90;
        if (dir == CLOCKWISE)
        {
            desiredYaw += incr;
        }
        else
        {
            desiredYaw -= incr;
        }

        if (desiredYaw > 180)
            desiredYaw -= 360;
        if (desiredYaw < -180)
            desiredYaw += 360;

        return desiredYaw;
    }
};