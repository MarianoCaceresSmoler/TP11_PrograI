#ifndef HARDWARE_H_
#define HARDWARE_H_

#define NUM_LEDS 8

extern const int leds_gpios[NUM_LEDS];

void hardware_init(void); // Inicializa el hardware: exporta, configura como salida y apaga todos los LEDs
void hardware_cleanup(void); // Libera todos los recursos GPIO exportados luego de haberlos usado
void turn_on_LED(int num); // Funcion para prender un LED
void turn_off_LED(int num); // Funcion para apagar un LED
void toggle_LED(int num); // Funcion para invertir el estado de un LED
void toggle_all_LEDs(void); // Funcion para invertir todos los LEDs
void turn_on_all_LEDs(void); // Funcion para prender todos los LEDs
void turn_off_all_LEDs(void); // Funcion para apagar todos los LEDs

#endif /* HARDWARE_H_ */

