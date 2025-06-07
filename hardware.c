#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hardware.h"

// Definición de los pines GPIO conectados a los LEDs
const int led_gpios[NUM_LEDS] = {17, 4, 18, 23, 24, 25, 22, 27}; 

// Exporta el GPIO para poder usarlo desde el user space
static void export_gpio(int gpio)
{
    FILE * handle;
    int nWritten;

    if ((handle = fopen("/sys/class/gpio/export", "w")) == NULL) // Abre el archivo de export del GPIO en modo escritura
    {
        printf("Cannot open export file\n");
        exit(1);
    }

    nWritten = fprintf(handle, "%d", gpio); // Escribe el GPIO correspondiente en el archivo

    if(nWritten == -1)
    {
        printf("Cannot export gpio %d\n", gpio);
        exit(1);
    }
    else
    {
        printf("Exported gpio %d succesfully\n", gpio);
    }

    fclose(handle);
    
}

// Devuelve el GPIO al KernelSpace
static void unexport_gpio(int gpio)
{
    FILE * handle; // Abre el archivo de unexport del GPIO en modo escritura
    int nWritten;

    if ((handle = fopen("/sys/class/gpio/unexport", "w")) == NULL)
    {
        printf("Cannot open unexport file\n");
        exit(1);
    }

    nWritten = fprintf(handle, "%d", gpio); // Escribe el GPIO correspondiente en el archivo

    if (nWritten == -1) {
        printf("Cannot unexport gpio %d\n", gpio);
        exit(1);
    }
    else
    {
        printf("Unexported gpio %d succesfully\n", gpio);
    }

    fclose(handle);

}

// Configura la dirección del GPIO ("in" o "out")
static void set_gpio_direction(int gpio, char * direction)
{
    FILE * handle;
    int nWritten;

    char path[100]; 
    sprintf(path, "/sys/class/gpio/gpio%d/direction", gpio); // Configura la ruta al archivo de dirección del GPIO


    if ((handle = fopen(path, "w")) == NULL) // Abre el archivo de dirección del GPIO en modo escritura
    {
        printf("Cannot open directiion file\n");
        exit(1);
    }

    // Escribe la dirección deseada en el archivo
    if((nWritten = fputs(direction, handle)) == -1)
    {
        printf("Cannot set gpio direction\n");
        exit(1);
    }else
    {
        printf("Set direction of gpio %d succesfully\n", gpio);
    }

    fclose(handle);
    
}

// Establece el valor del GPIO (0 o 1)
static void set_gpio_value(int gpio, int value)
{
    FILE * handle;

    char path[100]; 
    sprintf(path, "/sys/class/gpio/gpio%d/value", gpio); // Configura la ruta al archivo del valor del GPIO

    if ((handle = fopen(path, "w")) == NULL) // Abre el archivo del valor del GPIO en modo escritura
    {
        printf("Cannot open value file\n");
        exit(1);
    }

    char char_value = value ? '1' : '0'; // Convierte el valor a char para escribirlo en el archivo

    // Escribe el valor deseado en el archivo
    if((fputc(char_value, handle)) == -1)
    {
        printf("Cannot write gpio value\n");
        exit(1);
    }else
    {
        printf("Set value of gpio %d succesfully\n", gpio);
    }

    fclose(handle);
    
}

// Lee el valor actual del GPIO y lo devuelve como entero
static int read_gpio_value(int gpio)
{
    FILE * handle;

    char path[100], value_str[5]; 
    sprintf(path, "/sys/class/gpio/gpio%d/value", gpio); // Configura la ruta al archivo del valor del GPIO

    if ((handle = fopen(path, "r")) == NULL) // Abre el archivo del valor del GPIO en modo lectura
    {
        printf("Cannot open value file\n");
        exit(1);
    }

    // Lee el contenido del archivo
    if(fgets(value_str, sizeof(value_str), handle) == NULL)
    {
        printf("Cannot read gpio value\n");
    }
    else
    {
        printf("Read value of gpio %d succesfully\n", gpio);
    }

    fclose(handle);
    return atoi(value_str); // Convierte el string leído a int y lo devuelve

}

// Inicializa el hardware: exporta, configura como salida y apaga todos los LEDs
void hardware_init(void)
{
    int i;

    for (i = 0; i < NUM_LEDS; i++)
    {
        export_gpio(led_gpios[i]); // Exporta el GPIO
        set_gpio_direction(led_gpios[i], "out"); // Setea el GPIO como salida
        set_gpio_value(led_gpios[i], 0); // Setea el valor del GPIO a 0 (apaga el LED)
    }
}

// Libera todos los GPIOs luego de haberlos usado
void hardware_cleanup(void)
{
    for (int i = 0; i < NUM_LEDS; i++) {
        unexport_gpio(led_gpios[i]); // Desexporta el GPIO
    }
}

// Enciende el LED indicado si el índice es válido
void turn_on_LED(int led) {
    if (led >= 0 && led < NUM_LEDS) set_gpio_value(led_gpios[led], 1);
}

// Apaga el LED indicado si el índice es válido
void turn_off_LED(int led) {
    if (led >= 0 && led < NUM_LEDS) set_gpio_value(led_gpios[led], 0);
}

// Invierte el estado del LED indicado si el índice es válido
void toggle_LED(int led) {
    if (led >= 0 && led < NUM_LEDS) set_gpio_value(led_gpios[led], !read_gpio_value(led_gpios[led]));
}

// Invierte el estado de todos los LEDs
void toggle_all_LEDs(void)
{
    int i;

    for (i = 0; i < NUM_LEDS; i++)
    {
        set_gpio_value(led_gpios[i], !read_gpio_value(led_gpios[i]));
    }
}

// Enciende todos los LEDs
void turn_on_all_LEDs(void)
{
    int i;

    for (i = 0; i < NUM_LEDS; i++)
    {
        set_gpio_value(led_gpios[i], 1);
    }
}

// Apaga todos los LEDs
void turn_off_all_LEDs(void)
{
    int i;

    for (i = 0; i < NUM_LEDS; i++)
    {
        set_gpio_value(led_gpios[i], 0);
    }
}


