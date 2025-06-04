#ifndef LEDS_H_
#define LEDS_H_

void init_leds(int number);
void turnOnLED(int numero); // Funcion para prender un LED
void toggleAllLEDs(void); // Funcion para alternar todos los LEDs
void turnOnAllLEDs(void); // Funcion para prender todos los LEDs
void turnOffAllLEDs(void); // Funcion para apagar todos los LEDs
void showLEDs(void); // Funcion para mostrar el estado de los LEDs

#endif /* LEDS_H_ */
