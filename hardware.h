#ifndef HARDWARE_H_
#define HARDWARE_H_

#define NUM_LEDS 8

extern const int leds_gpios[NUM_LEDS];

void hardware_init(void);


#endif /* HARDWARE_H_ */
