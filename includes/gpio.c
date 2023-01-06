#include "gpio.h"

int init_gpios(void) {
	if (gpioInitialise() < 0) {
		fprintf(stderr, "[-] gpioInitialise() raised an error...");
		return -1;
	}
	gpioSetMode(24, PI_OUTPUT);
	return 0;
}

void setLedState(int pin, int state) {
	//Just initialize GPIO LED pin to 24 for now
	gpioWrite(pin, state);
}

int destroy_gpio(void) {
	gpioTerminate();
	return 0;
}
