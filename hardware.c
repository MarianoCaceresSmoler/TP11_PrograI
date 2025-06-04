#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hardware.h"

const int led_gpios[NUM_LEDS] = {17, 4, 18, 23, 24, 25, 22, 27}; 

static void export_gpio(int gpio)
{
    FILE * handle;
    int nWritten;

    if ((handle = fopen("sys/classs/gpio/export", "w")) == NULL)
    {
        printf("Cannot open EXPORT file\n");
        exit(1);
    }

    nWritten = fprintf(handle, "%d", gpio);

    if(nWritten == -1)
    {
        printf("Cannot EXPORT PIN %d\n", gpio);
        exit(1);
    }
    else
    {
        printf("EXPORTED PIN %d succesfully\n", gpio);
    }

    fclose(handle);
    
}


static void set_gpio_direction(int gpio, char * direction)
{
    FILE * handle;
    int nWritten;

    char directory[100] = "sys/classs/gpio/gpio"; 
    sprintf(directory, "%d", gpio);
    strcat(directory, "/direction");

    if ((handle = fopen(directory, "w")) == NULL)
    {
        printf("Cannot open DIRECTION file\n");
        exit(1);
    }

    // Set pin direction

    if((nWritten = fputs(direction, handle)) == -1)
    {
        printf("Cannot open DIRECTION pin\n");
        exit(1);
    }else
    {
        printf("SET DIRECTION of PIN %d succesfully\n", gpio);
    }

    fclose(handle);
    
}

static void set_gpio_value(int gpio, int value)
{
    FILE * handle;
    int nWritten;

    char directory[100] = "sys/classs/gpio/gpio"; 
    sprintf(directory, "%d", gpio);
    strcat(directory, "/value");

    if ((handle = fopen(directory, "w")) == NULL)
    {
        printf("Cannot open DEVICE file\n");
        exit(1);
    }

    // Set pin value

    char char_value = (char)value;

    if((fputc(value, handle)) == -1)
    {
        printf("Cannot write pin VALUE\n");
        exit(1);
    }else
    {
        printf("SET VALUE of PIN %d succesfully\n", gpio);
    }

    fclose(handle);
    
}


void hardware_init(void)
{
    int i;

    for (i = 0; i < NUM_LEDS; i++)
    {
        export_gpio(i);
        set_direction(i, "out");
        set_gpio_value(i, 0);
    }

}

