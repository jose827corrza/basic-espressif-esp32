#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t taskHandle1 = NULL;
TaskHandle_t taskHandle2 = NULL;

void task1(void *args){
    int count = 0;
    while(1){
        printf("Task 1, with count: %d\n", count);
        count++;
        if(count == 5){
            // As argument receiver the task to be deleted, if none is provided, deletes the current one.
            printf("Task 2 suspended\n");
            vTaskSuspend(taskHandle2);
        }
        if(count == 10){
            // As argument receiver the task to be deleted, if none is provided, deletes the current one.
            printf("Task 2 Resumed\n");
            vTaskResume(taskHandle2);
        }
        if(count == 12){
            // As argument receiver the task to be deleted, if none is provided, deletes the current one.
            printf("Task 2 Deleted\n");
            vTaskDelete(taskHandle2);
        }
        if(count == 15){
            // As argument receiver the task to be deleted, if none is provided, deletes the current one.
            printf("Task 1 Deleted\n");
            vTaskDelete(NULL);
        }
        
    }
}
void task2(void *args){
    int count = 0;
    while(1){
        printf("Task 2, with count: %d\n", count);
        count++;
        if(count == 15){
            // As argument receiver the task to be deleted, if none is provided, deletes the current one.
            vTaskDelete(NULL);
        }
    }
}

void app_main(void)
{
    // task, task name, memmory, variables to the task, priority, taskhandle
    xTaskCreate(task1, "task_1", 4096, NULL, 10, &taskHandle1);
    // This sets which  core is used to the task
    xTaskCreatePinnedToCore(task2, "task_2", 4096, NULL, 10, &taskHandle2,1);
}
