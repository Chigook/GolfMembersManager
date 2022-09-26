#include "ServoMotor.h"

ServoMotor::ServoMotor(int pin) : pwmpin(pin)
{
    wiringPiSetup();
    pinMode(pwmpin, OUTPUT);
}

ServoMotor::~ServoMotor()
{

}

bool ServoMotor::servomotor_open2sec()
{
    softPwmCreate(pwmpin, 0, 200);
    softPwmWrite(pwmpin, 20);
    delay(2000);
    softPwmWrite(pwmpin, 10);
    delay(1000);
    softPwmStop(pwmpin);
    return true;
}