#include "hardware.h"
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
#define PROGRAM_CONTINUE 1

int main(void)
{

	hardware_init();

	char input, sigCar;
	int programStatus = PROGRAM_CONTINUE;

	do
	{
		programStatus = PROGRAM_CONTINUE;

		printf("\nLEDs controller \n - Insert a number between 0 and 7 to toggle a LED \n - Insert t to toggle all LEDs \n - Insert s to turn on all LEDs \n - Insert c to turn off all LEDs \n - Insert q to exit \n");
		input = getchar();

		if((sigCar = getchar()) == '\n') // Verifica que el usuario ingresa un unico caracter
		{
			if(input >= '0' && input <= '7') // Si el usuario ingresa un numero valido, invierte el LED correspondiente
			{
				int led = (int) (input - 48);
				toggle_LED(led);
			}
			else
			{
				switch(input) // Si el usuario ingresa un caracter valido, ejecuta la accion correspondiente
				{
				case TOGGLE:
					toggle_all_LEDs();
					break;
				case TURN_ON:
					turn_on_all_LEDs();
					break;
				case TURN_OFF:
					turn_off_all_LEDs();
					break;
				case EXIT:
					programStatus = PROGRAM_END; // Cambia el estado del programa para finalizar en caso de que ingrese 'q'
					break;
				default:
					printf(ERROR_MESSAGE);
					break;
				}
			}
		}
		else
		{
			printf(ERROR_MESSAGE);
		}

		if(sigCar != '\n') CLEAN_BUFFER; // Limpia buffer unicamente si es necesario

	} while(programStatus != PROGRAM_END);

	hardware_cleanup();

	return 0;

}


