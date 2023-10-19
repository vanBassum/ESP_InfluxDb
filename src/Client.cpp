#include <stdio.h>
#include "esp_log.h"
#include "Client.h"

using namespace Influx;






Client::Client(const std::string url, const std::string token, const std::string organisation, const std::string bucket)
    : url(url)
    , token(token)
    , organisation(organisation)
    , bucket(bucket)
    , config{
        .host = url.c_str(),
        .path = "/api/v2/write",
        .query = "",
        .disable_auto_redirect = true,
        .event_handler = _http_event_handler
    }
{
    client = esp_http_client_init(&config);
    esp_http_client_set_header(client, "Accept", "application/json");
    esp_http_client_set_header(client, "Content-Type", "text/plain; charset=utf-8");

    std::string authHeader = "Token " + token;
    esp_http_client_set_header(client, "Authorization", authHeader.c_str());
}

Client::~Client()
{
    esp_http_client_cleanup(client);
}

esp_err_t Client::_http_event_handler(esp_http_client_event_t *evt)
{
    return ESP_OK;
}

int Client::SendLine(std::string line)
{
    const char *post_data = line.c_str();
    std::string writeUrl = url + "/api/v2/write" + "?org=" + organisation + "&bucket=" + bucket + "&precision=ns";
    esp_http_client_set_url(client, writeUrl.c_str());
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_post_field(client, post_data, strlen(post_data));

    ESP_LOGI(TAG, "Query = '%s'", post_data);

    esp_err_t err = esp_http_client_perform(client);
    
    if(err) 
    {
        ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
        return err;
    }
    
    int code = esp_http_client_get_status_code(client);
    if(code >= 200 || code <= 204)
        ESP_LOGI(TAG, "HTTP POST Status = %d", code);
    else
        ESP_LOGE(TAG, "HTTP POST Status = %d", code);
    return code;
}