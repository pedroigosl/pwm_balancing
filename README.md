# pwm_balancing

Library for normalizing PWM signals into a [0,255] range. Modes with absolute values from bottom to top and with mid value with threshold for distance from center 

## +++ WARNING +++

This library is untested. It is part of a greater project still on its beginnings

## Structure

The library models balancer objects with top, bottom and resting values, with optional threshold for resting and out of resting values. Gets value and normalize into [0, 255] or [-255, 255]

## How to use

1 - You first need to instantiate a balancer and set your limits and parameter. You can either do it all directly using constructors or use ***set*** functions later

2 - Use the object's normalizing functions on incoming pwm signal
- ***getValueABS***
- ***getValueRLT***

3 - If needed, you can recover values using ***get*** functions

## Example

```C++
#include <Arduino.h>

void setup() {
  ...
  bwmBalancer balancer;
  ...
}

void loop() {
  ...
  balancer.setAll(input_pin, 5000);
  ...
  normalized = balancer.getValueRLT(pwm_reading);
  ...
}
```

## License
[MIT](https://choosealicense.com/licenses/mit/)