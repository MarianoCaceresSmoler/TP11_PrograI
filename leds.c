#include "leds.h"
#include "hardware.h"
#include <stdio.h>

void init_leds(int number)
{
	hardware_init();
}

void turn_on_led(int number)
{
	bitSet(number);
}

void toggle_all_leds(void)
{
	maskToggle(0xFF);
}

void turn_on_all_leds(void)
{
	maskOn(0xFF);

}

void turn_off_all_leds(void)
{
	maskOff(0xFF);
}

