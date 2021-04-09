#include <Adafruit_MotorShield.h>

enum class Speed : uint8_t
{
    FAST,
    SLOWER,
    SLOW
};

class Chassis
{
    static const inline uint8_t speeds[3] = {255, 125, 80};
    Adafruit_MotorShield shield;

    struct Motor
    {
        Adafruit_DCMotor *motor;
        uint8_t state;
        uint8_t speed;
    };
    enum
    {
        LEFT = 0,
        RIGHT = 1
    };

    Motor motors[2] = {{shield.getMotor(1), RELEASE, 0}, {shield.getMotor(2), RELEASE, 0}};

public:
    void begin() {
        shield.begin();
    }

public:
    void stop()
    {
        state(LEFT, RELEASE);
        state(RIGHT, RELEASE);
    }

    void forward(Speed spd)
    {
        speed(spd);
        state(LEFT, FORWARD);
        state(RIGHT, FORWARD);
    }

    void back(Speed spd)
    {
        speed(spd);
        state(LEFT, BACKWARD);
        state(RIGHT, BACKWARD);
    }

    void clockwise(Speed spd)
    {
        speed(spd);
        state(LEFT, FORWARD);
        state(RIGHT, BACKWARD);
    }

    void counterclockwise(Speed spd)
    {
        speed(spd);
        state(LEFT, BACKWARD);
        state(RIGHT, FORWARD);
    }

    void state(uint8_t side, uint8_t newState)
    {
        auto &m = motors[side];
        if (m.state != newState)
        {
            m.motor->run(m.state = newState);
        }
    }

    void speed(Speed spd)
    {
        speed(LEFT, speeds[(uint8_t)spd]);
        speed(RIGHT, speeds[(uint8_t)spd]);
    }

    void speed(uint8_t side, uint8_t newSpeed)
    {
        auto &m = motors[side];
        if (m.speed != newSpeed)
        {
            m.motor->run(m.speed = newSpeed);
        }
    }
};