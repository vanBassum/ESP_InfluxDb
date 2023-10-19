#pragma once
#include <string>
#include <vector>
#include "esp_system.h"


namespace Influx
{
    class Client;
    class Point
    {
        std::string measurement;
        std::vector<std::string> tagSet;
        std::vector<std::string> fieldSet;
        uint64_t timestamp;
        std::string GetQuery();
    public:
        Point(const std::string measurement);
        ~Point();
        Point& AddTag(const std::string name, const std::string value);
        Point& AddField(const std::string name, const float value);
        Point& AddField(const std::string name, const int64_t value);
        Point& AddField(const std::string name, const uint64_t value);
        Point& AddField(const std::string name, const std::string value);
        Point& AddField(const std::string name, bool value);
        Point& SetTimestamp(const uint64_t unix);
        void Post(Client& client);
    };
}






