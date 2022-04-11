#include "pwm_balancing.h"

pwmBalancer::pwmBalancer()
{
}

pwmBalancer::~pwmBalancer()
{
}

void pwmBalancer::setLimits(int pwm_input)
{
}

void pwmBalancer::setResting(int pwm_input, int threshold = 0)
{
}

void pwmBalancer::setAll(int pwm_input, int threshold = 0)
{
}

int norm255(int v_in, int v_min, int v_max)
{
    return (int)(255.0 * ((float)(v_in - v_min) / (float)(v_max - v_min)));
}

int pwmBalancer::getValueABS(int pwm_input)
{
    try
    {
        if (top_value == NULL || bottom_value == NULL)
        {
            throw;
        }
    }
    catch (...)
    {
        return -256;
    }
    if (pwm_input > top_value)
    {
        top_value = pwm_input;
    }
    if (pwm_input < bottom_value)
    {
        bottom_value = pwm_input;
    }
    return norm255(pwm_input, bottom_value, top_value);
}

int pwmBalancer::getValueRLT(int pwm_input)
{
    try
    {
        if (top_value == NULL || bottom_value == NULL || resting_value == NULL)
        {
            throw;
        }
    }
    catch (...)
    {
        return -256;
    }
    if (pwm_input >= resting_value)
    {
        if (pwm_input > top_value)
        {
            top_value = pwm_input;
        }
        return norm255(pwm_input, resting_value, top_value);
    }
    if (pwm_input < bottom_value)
    {
        bottom_value = pwm_input;
    }
    return -norm255(pwm_input, bottom_value, resting_value);
}