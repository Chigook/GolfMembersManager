#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#pragma once
#include <softPwm.h>
#include <wiringPi.h>

class ServoMotor
{
private:
    int pwmpin;

public:
    ServoMotor(int pin);
    ~ServoMotor();
    bool servomotor_open2sec();

};

#endif