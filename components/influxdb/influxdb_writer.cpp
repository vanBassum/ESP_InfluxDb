
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

        void InfluxDBWriter::loop()
        {
            if (this->http_ == nullptr || pending_lines_.empty())
                return;

            std::string body;

            // Pop up to MAX_QUEUE_SIZE entries
            for (size_t i = 0; i < MAX_QUEUE_SIZE && !pending_lines_.empty(); i++)
            {
                body += pending_lines_.front() + "\n";
                pending_lines_.pop_front(); // Safe: modifies only one item at a time
            }

            std::string full_url = this->url_ + "?org=" + this->org_ + "&bucket=" + this->bucket_ + "&precision=s";

            std::list<esphome::http_request::Header> headers = {
                {"Authorization", "Token " + this->token_},
                {"Content-Type", "text/plain"}};

            ESP_LOGD(TAG, "Sending up to %d lines to InfluxDB", MAX_QUEUE_SIZE);
            this->http_->post(full_url, body, headers);
        }

        void InfluxDBWriter::on_sensor_update(sensor::Sensor *obj, float state)
        {
            if (!std::isfinite(state))
                return;

            time_t timestamp = time(nullptr);

            std::string sensor_id = obj->get_object_id();
            std::replace(sensor_id.begin(), sensor_id.end(), ' ', '_');

            std::string line = this->measurement_ +
                               ",sensor=" + sensor_id +
                               " value=" + esphome::to_string(state) +
                               " " + esphome::to_string(timestamp);

            if (pending_lines_.size() >= MAX_QUEUE_SIZE)
            {
                // Discard oldest
                pending_lines_.pop_front();
            }

            pending_lines_.push_back(std::move(line));
            ESP_LOGD(TAG, "Queued InfluxDB line: %s", pending_lines_.back().c_str());
        }

    } // namespace influxdb
} // namespace esphome
