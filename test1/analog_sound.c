#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#define ADC_NUM 0
#define ADC_PIN 26

#define ADC_VREF 3.3 // input single varies in between 0 and 3.3 volts
#define ADC_RANGE (1 << 12) // the number is represented by 12 bits
#define ADC_CONVERT (ADC_VREF / (ADC_RANGE - 1)) // thats how we will identify the voltage from the analog pin

#define LED_25 25

uint16_t map(uint16_t val, uint16_t min, uint16_t max, uint16_t min_new, uint16_t max_new){
    return (val - min) * (max_new - min_new) / (max - min) + min_new;
}

int main(void){
    bool usb_state = stdio_usb_init();
    
    adc_init();

    adc_gpio_init(ADC_PIN);
    adc_select_input(ADC_NUM);

    gpio_init(LED_25);
    gpio_set_dir(LED_25, GPIO_OUT);

    if (usb_state)
        gpio_put(LED_25, 1);
    
    uint16_t raw_adc;
    uint16_t max_adc = 0;
    uint16_t min_adc = 0;
    uint16_t current_adc = 0;
    u_int8_t i = 0;

    while (true)
    {
        max_adc = 0;
        min_adc = 4095;
        for (i = 0; i < 10; i++){
            current_adc = adc_read();
            if (current_adc < min_adc)
                min_adc = current_adc;
            
            if (min_adc > max_adc)
                max_adc = min_adc;
        }
        raw_adc = max_adc - min_adc;
        printf("%d\n", raw_adc);
        // printf("max = %d, min = %d, diff = %d, %.2f\n",max_adc, min_adc, raw_adc, raw_adc * ADC_CONVERT);
        // raw_adc = adc_read(); // reading the raw voltage from the selected adc input above        
        // printf("%d , %d, %.2f\n", raw_adc, map(raw_adc, 0, 4095, 0, 255), raw_adc * ADC_CONVERT);
        // sleep_ms(10);
    }
    
}