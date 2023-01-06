#ifndef GPIO_H_
#define GPIO_H_

#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>

//GPIO State Enum
enum GPIO_STATE {
	GPIO_LOW,
	GPIO_HIGH
};

//Initialize the GPIOs
int init_gpios(void);

//Set the LED state
void setLedState(int pin, int state);

//Destroy GPIO
int destroy_gpio(void);

#endif
