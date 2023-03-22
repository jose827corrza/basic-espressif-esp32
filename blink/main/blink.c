#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Changes at compilation time the nave for the value in the whole code: LED_PIN -> 2
#define LED_PIN 2
#define DELAY_MS 1000

void app_main(void)
{
    int led_state = 0;
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(LED_PIN, led_state);
        led_state = !led_state;
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS); // The last represents time that processor uses between tasks
    }
}
