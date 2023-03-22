#include <stdio.h>
#include "esp_wifi.h"
#include "nvs_flash.h"

// This library was included to ease the implementation of a WiFi conn, for this particular example
#include "protocol_examples_common.h"
// To be able to create a web server
#include "esp_http_server.h"

#include "string.h" // To use the strLeng in response of the handler

// static esp_err_t api_get_handler(httpd_req_t *req){
//     httpd_resp_set_hdr(req, "Content-Type", "application/json");
//     httpd_resp_send(req, "ALO ALO jose", HTTPD_RESP_USE_STRLEN);
//     return ESP_OK;
// }
static esp_err_t json_get_handler(httpd_req_t *req){
    httpd_resp_set_hdr(req, "Content-Type", "application/json");
    char res[40];
    int test = 0;
    sprintf(res, "{ \"status\": 200, \"message\": %d}", test);
    httpd_resp_send(req, res, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// static const httpd_uri_t api = {
//     .uri = "/api",
//     .method = HTTP_GET,
//     .handler = api_get_handler
// };
static const httpd_uri_t json = {
    .uri = "/json",
    .method = HTTP_GET,
    .handler = json_get_handler
};

void web_server_init(){
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    if(httpd_start(&server, &config) != ESP_OK){
        printf("Error starting the server\n");
    } else{
        // httpd_register_uri_handler(server, &api); // Is a reference because is a whole group of data
        httpd_register_uri_handler(server, &json); // Is a reference because is a whole group of data
    }
}

void app_main(void)
{
    nvs_flash_init();
    esp_netif_init(); // Creates the Network interface
    esp_event_loop_create_default(); // Bring to the context the event loop that uses the esp32

    example_connect(); // Comes from the example and simplify the conn
    
    esp_netif_ip_info_t ip_info;
    esp_netif_t* netif=NULL;
    netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");

    if(netif == NULL) {
        printf("There is no network interface\n");
    } else{
        esp_netif_get_ip_info(netif, &ip_info);
        printf("IP: %d.%.d.%d.%d\n", IP2STR(&ip_info.ip));
        web_server_init();
    }

}
