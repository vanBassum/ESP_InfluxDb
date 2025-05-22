#pragma once

#include "esphome/core/component.h"
#include "esphome/components/http_request/http_request.h"
#include "esphome/components/sensor/sensor.h"
#include <deque>

namespace esphome
{
    namespace influxdb
    {

        class InfluxDBWriter : public Component
        {
        public:
            InfluxDBWriter() = default;

            void setup() override;
            void loop() override;
            float get_setup_priority() const override { return setup_priority::AFTER_WIFI; }

            void set_url(const std::string &url) { this->url_ = url; }
            void set_token(const std::string &token) { this->token_ = token; }
            void set_org(const std::string &org) { this->org_ = org; }
            void set_bucket(const std::string &bucket) { this->bucket_ = bucket; }
            void set_measurement(const std::string &measurement) { this->measurement_ = measurement; }
            void set_http(esphome::http_request::HttpRequestComponent *http) { this->http_ = http; }

            void on_sensor_update(sensor::Sensor *obj, float state);

        protected:
            std::string url_;
            std::string token_;
            std::string org_;
            std::string bucket_;
            std::string measurement_;

            std::deque<std::string> pending_lines_;
            static constexpr size_t MAX_QUEUE_SIZE = 10;

            esphome::http_request::HttpRequestComponent *http_{nullptr};
        };

    } // namespace influxdb
} // namespace esphome
