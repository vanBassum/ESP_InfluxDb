
#include "influxdb_writer.h"
#include <cmath>
#include <algorithm>
#include "esphome/core/application.h"

namespace esphome
{
    namespace influxdb
    {

        static const char *const TAG = "influxdb";

        void InfluxDBWriter::setup()
        {
            ESP_LOGCONFIG(TAG, "Setting up InfluxDB Writer...");

            for (auto *obj : App.get_sensors())
            {
                if (obj->is_internal())
                    continue;

                obj->add_on_state_callback([this, obj](float state)
                                           { this->on_sensor_update(obj, state); });
            }
        }

        void InfluxDBWriter::on_sensor_update(sensor::Sensor *obj, float state)
        {
            if (!std::isfinite(state) || this->http_ == nullptr)
                return;

            // Get current timestamp in seconds
            time_t timestamp = time(nullptr);

            // Escape sensor ID for InfluxDB tags
            std::string sensor_id = obj->get_object_id();
            std::replace(sensor_id.begin(), sensor_id.end(), ' ', '_');

            std::string line = this->measurement_ 
                                + ",sensor=" + sensor_id 
                                + " value=" + esphome::to_string(state) 
                                + " " + esphome::to_string(timestamp);

            std::string full_url = this->url_ + "?org=" + this->org_ + "&bucket=" + this->bucket_ + "&precision=s";

            std::list<esphome::http_request::Header> headers = {
                {"Authorization: Token ", this->token_},
                {"Content-Type", "text/plain"}
            };

            ESP_LOGD(TAG, "Sending to InfluxDB: %s", line.c_str());

            this->http_->post(
                full_url,
                line,
                headers);
        }

    } // namespace influxdb
} // namespace esphome
