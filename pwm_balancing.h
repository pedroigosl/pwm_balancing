#ifndef PWM_BALANCING_H
#define PWM_BALANCING_H

#include "Arduino.h"

class pwmBalancer
{
public:
    pwmBalancer();
    ~pwmBalancer();
    // registers pwm signal limits
    void setLimits(int pwm_input);
    // registers pwm resting value, with threshold to what is considered 0
    void setResting(int pwm_input, int threshold);
    // both previous functions in one
    void setAll(int pwm_input, int threshold);
    // get value in [0, 255] from bottom to top
    int getValueABS(int pwm_input);
    // get value in [-255, 255] from bottom to top, where resting == 0
    int getValueRLT(int pwm_input);

private:
    int *top_value = NULL;
    int *bottom_value = NULL;
    int *resting_value = NULL;
    int threshold = 0;
};

#endif
