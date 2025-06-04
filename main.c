#include "hardware.h"
#include "leds.h"
#include <stdio.h>

// Macros para manejo de entradas
#define TOGGLE 't'
#define TURN_ON  's'
#define TURN_OFF 'c'
#define EXIT 'q'

#define ERROR_MESSAGE "\nInput is not valid: Enter a valid character\n" // Mensaje de error en caso de ingreso invalido

#define CLEAN_BUFFER while(getchar() != '\n') // Macro para limpiar el buffer de entrada de datos

// Macros de estado del programa
#define PROGRAM_END -1
#define PROGRAM_ERROR 0
#define PROGRAM_CONTINUE 1

int main(void)
{

	init_leds();

	char input, sigCar, programStatus = PROGRAM_CONTINUE;

	do
	{
		programStatus = PROGRAM_CONTINUE;

		printf("\nPort A controller \n - Insert a number between 0 and 7 to turn on a bit \n - Insert t to toggle all bits \n - Insert s to turn on all bits \n - Insert c to turn off all bits \n - Insert q to exit \n");
		input = getchar();

		if((sigCar = getchar()) == '\n') // Verifica que el usuario ingresa un unico caracter
		{
			if(input >= '0' && input <= '7')
			{
				int bit = (int) (input - 48);
				turnOnLED(bit);
			}
			else
			{
				switch(input)
				{
				case TOGGLE:
					toggleAllLEDs();
					break;
				case TURN_ON:
					turnOnAllLEDs();
					break;
				case TURN_OFF:
					turnOffAllLEDs();
					break;
				case EXIT:
					programStatus = PROGRAM_END; // Cambia el estado del programa para finalizar en caso de que ingrese 'q'
					break;
				default:
					programStatus = PROGRAM_ERROR; // Cambia el estado del programa para no mostrar el valor de los leds en caso de error
					printf(ERROR_MESSAGE);
					break;
				}
			}
		}
		else
		{
			programStatus = PROGRAM_ERROR; // Cambia el estado del programa para no mostrar el valor de los leds en caso de error
			printf(ERROR_MESSAGE);
		}

		if(sigCar != '\n') CLEAN_BUFFER; // Limpia buffer unicamente si es necesario

	} while(programStatus != PROGRAM_END);

	return 0;

}


