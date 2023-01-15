#include <stdlib.h>
#include "pico/stdlib.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define EXTERNAL_LED 9

int main() {

    const uint LED_PIN = 25;

    bool usb_on = stdio_usb_init();

    gpio_init(LED_PIN);
    gpio_init(EXTERNAL_LED);

    gpio_set_dir(EXTERNAL_LED, GPIO_OUT);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    if (usb_on) {
        while (true) {
            printf("Hello World!");
            gpio_put(LED_PIN, GPIO_ON);
            gpio_put(EXTERNAL_LED, GPIO_ON);
            sleep_ms(1000);
            gpio_put(LED_PIN, GPIO_OFF);
            gpio_put(EXTERNAL_LED, GPIO_OFF);
            sleep_ms(1000);
        }
    }

}