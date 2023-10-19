#pragma once
#include <string>
#include "esp_system.h"
#include "esp_http_client.h"


namespace Influx
{
    class Client
    {
        constexpr const static char* TAG = "Influx::Client";
        const std::string url;
        const std::string token;
        const std::string organisation;
        const std::string bucket;

        esp_http_client_config_t config = {};
        esp_http_client_handle_t client;

        static esp_err_t _http_event_handler(esp_http_client_event_t *evt);

    public:
        Client(const std::string url, const std::string token, const std::string organisation, const std::string bucket);
        ~Client();
        int SendLine(std::string line);

    };
}






