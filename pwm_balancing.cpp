#include "pwm_balancing.h"

pwmBalancer::pwmBalancer()
{
}

pwmBalancer::~pwmBalancer()
{
}

void pwmBalancer::setLimits(int input_pin, int set_period_milli = setting_time)
{
    unsigned long start = millis();
    unsigned long current = millis();

    int input_value = analogRead(input_pin);
    top_value = input_value;
    bottom_value = input_value;

    while (current - start < set_period_milli)
    {
        input_value = analogRead(input_pin);
        if (input_value > top_value)
        {
            top_value = input_value;
        }
        if (input_value < bottom_value)
        {
            bottom_value = input_value;
        }
        current = millis();
    }
}

void pwmBalancer::setResting(int input_pin, int threshold = 0, int set_period_milli = setting_time)
{
    unsigned long start = millis();
    unsigned long current = millis();

    int input_value = analogRead(input_pin);
    int top_value_local = input_value;
    int bottom_value_local = input_value;

    while (current - start < set_period_milli)
    {
        input_value = analogRead(input_pin);
        if (input_value > top_value_local)
        {
            top_value_local = input_value;
        }
        if (input_value < bottom_value_local)
        {
            bottom_value_local = input_value;
        }
        current = millis();
    }
    resting_value = (top_value_local + bottom_value_local) / 2;
    this->threshold = threshold;
}

void pwmBalancer::setAll(int input_pin, int threshold = 0, int set_period_milli = setting_time)
{
    setLimits(input_pin, set_period_milli);
    setResting(input_pin, threshold, set_period_milli);
}

int pwmBalancer::norm255(int v_in, int v_min, int v_max)
{
    return (int)(255.0 * ((float)(v_in - v_min) / (float)(v_max - v_min)));
}

int pwmBalancer::inThreshold(int pwm_input, int center_val, int threshold)
{
    int limits[2];
    limits[0] = (int)((float)center_val - ((float)center_val * ((float)threshold / 100.0)));
    limits[1] = (int)((float)center_val + ((float)center_val * ((float)threshold / 100.0)));
    if (pwm_input >= limits[0] && pwm_input <= limits[1])
    {
        return center_val;
    }
    return pwm_input;
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

    int end_value = inThreshold(pwm_input, resting_value, threshold);
    if (pwm_input >= resting_value)
    {
        if (pwm_input > top_value)
        {
            top_value = pwm_input;
        }
        return norm255(end_value, resting_value, top_value);
    }
    if (pwm_input < bottom_value)
    {
        bottom_value = pwm_input;
    }
    return -norm255(end_value, bottom_value, resting_value);
}