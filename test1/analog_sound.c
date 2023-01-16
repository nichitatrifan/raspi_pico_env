#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"
#include "hardware/adc.h"

#define ADC_NUM 0
#define ADC_PIN (26 + ADC_NUM)

#define ADC_VREF 3.3 // input single varies in between 0 and 3.3 volts
#define ADC_RANGE (1 << 12) // the number is represented by 12 bits
#define ADC_CONVERT (ADC_VREF / (ADC_RANGE - 1)) // thats how we will identify the voltage from the analog pin

uint16_t map(uint16_t val, uint16_t min, uint16_t max, uint16_t min_new, uint16_t max_new){
    return (val - min) * (max_new - min_new) / (max - min) + min_new;
}

int main(void){
    bool usb_state = stdio_usb_init();
    
    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(ADC_NUM);
    
    uint16_t raw_adc;

    while (true)
    {
        raw_adc = adc_read(); // reading the raw voltage from the selected adc input above
        // printf("%.2f\n", raw_adc * ADC_CONVERT);
        printf("%d , %d\n", raw_adc, map(raw_adc, 0, 4095, 0, 255));
        sleep_ms(60);
    }
    
}