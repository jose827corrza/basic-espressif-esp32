#include <stdio.h>
#include "freertos/FreeRTOS.h"
// Storage
#include "nvs_flash.h"
#include "nvs.h"

void app_main(void)
{
    printf("start\n");

    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    printf("NVS init\n");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    // Access to the storage
    nvs_handle_t myStorage;
    err = nvs_open("storage", NVS_READWRITE, &myStorage);// name, permissions, variable thtat receives
    printf("NVS open\n");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    // Set a value in the storage
    err = nvs_set_i32(myStorage, "number", 13);
    printf("NVS Set\n");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    // To save 
    err = nvs_commit(myStorage);
    printf("NVS Commit\n");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    // Read value in the volatile memmory
    int32_t number;
    err = nvs_get_i32(myStorage, "number", &number);
    printf("NVS Get\n");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    printf("El valor recuperado es: %li\n", number);
    // Close the conn is very important, to be eficient.
    nvs_close(myStorage);

    printf("End\n");

}
