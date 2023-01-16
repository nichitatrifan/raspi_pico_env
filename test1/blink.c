#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define SOUND_SENSOR 2
#define DEFAULT_LED 25

int main() {

    bool usb_on = stdio_usb_init();
    bool sensor_state = true;

    gpio_init(SOUND_SENSOR);
    gpio_init(DEFAULT_LED);

    gpio_set_dir(SOUND_SENSOR, GPIO_IN);
    gpio_pull_up(SOUND_SENSOR);

    gpio_set_dir(DEFAULT_LED, GPIO_OUT);

    if (usb_on) {
        printf("Start collecting data:\n");
        while (true) {
            sensor_state = gpio_get(SOUND_SENSOR);
            if (sensor_state)
            {
                // printf("1\n");
                gpio_put(DEFAULT_LED, 1);                
            }else{
                // printf("0\n");
                gpio_put(DEFAULT_LED, 0);
            }
            
        }
    }

}