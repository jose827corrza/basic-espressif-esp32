#include <stdio.h>
#include "esp_chip_info.h"

void app_main()
{
    // Creating the variable
    esp_chip_info_t chip_info;

    // Setting where the info is stored
    esp_chip_info(&chip_info);

    printf("This is a chip family %s, and has %d cores!\n",
        CONFIG_IDF_TARGET,
        chip_info.cores
    );
}
