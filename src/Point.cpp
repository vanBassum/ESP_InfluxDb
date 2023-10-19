#include "Point.h"
#include "Client.h"

using namespace Influx;



    Point::Point(const std::string measurement)
    {
        this->measurement = measurement;
    }

    Point::~Point()
    {

    }

    Point& Point::AddTag(const std::string name, const std::string value)
    {
        tagSet.push_back(name + "=" + value);
        return *this;
    }

    Point& Point::AddField(const std::string name, const float value)
    {
        fieldSet.push_back(name + "=" + std::to_string(value));
        return *this;
    }

    Point& Point::AddField(const std::string name, const int64_t value)
    {
        fieldSet.push_back(name + "=" + std::to_string(value));
        return *this;
    }

    Point& Point::AddField(const std::string name, const uint64_t value)
    {
        fieldSet.push_back(name + "=" + std::to_string(value));
        return *this;
    }

    Point& Point::AddField(const std::string name, const std::string value)
    {
        fieldSet.push_back(name + "=" + value);
        return *this;
    }

    Point& Point::AddField(const std::string name, bool value)
    {
        fieldSet.push_back(name + "=" + (value?"t":"f"));
        return *this;
    }

    Point& Point::SetTimestamp(const uint64_t unix)
    {
        timestamp = unix;
        return *this;
    }

    void Point::Post(Client& client)
    {
        client.SendLine(GetQuery());
    }


std::string Point::GetQuery()
{
    std::string query;
    query += measurement;

    // Add tags if available
    if (!tagSet.empty())
    {
        query += ",";
        for (const auto& tag : tagSet)
        {
            query += tag + ",";
        }
        // Remove the trailing comma
        query.pop_back();
    }

    // Add fields if available
    if (!fieldSet.empty())
    {
        query += " ";
        for (const auto& field : fieldSet)
        {
            query += field + ",";
        }
        // Remove the trailing comma
        query.pop_back();
    }

    // Add timestamp
    query += " " + std::to_string(timestamp);

    return query;
}