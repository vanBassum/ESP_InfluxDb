import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.core import coroutine_with_priority  # ✅ Use this import now

from esphome.const import CONF_ID

DEPENDENCIES = ["network"]

influxdb_ns = cg.esphome_ns.namespace("influxdb")
InfluxDBWriter = influxdb_ns.class_("InfluxDBWriter", cg.Component, cg.Controller)

http_request_ns = cg.esphome_ns.namespace("http_request")
HttpRequestComponent = http_request_ns.class_("HttpRequestComponent")
HttpRequestIDF = http_request_ns.class_("HttpRequestIDF")

CONF_INFLUXDB_URL = "url"
CONF_INFLUXDB_TOKEN = "token"
CONF_INFLUXDB_ORG = "org"
CONF_INFLUXDB_BUCKET = "bucket"
CONF_INFLUXDB_MEASUREMENT = "measurement"
CONF_HTTP_REQUEST_ID = "http_request_id"

CONFIG_SCHEMA = cv.All(
    cv.Schema({
        cv.GenerateID(): cv.declare_id(InfluxDBWriter),
        cv.Required(CONF_INFLUXDB_URL): cv.string,
        cv.Required(CONF_INFLUXDB_TOKEN): cv.string,
        cv.Required(CONF_INFLUXDB_ORG): cv.string,
        cv.Required(CONF_INFLUXDB_BUCKET): cv.string,
        cv.Required(CONF_INFLUXDB_MEASUREMENT): cv.string,
        cv.Required(CONF_HTTP_REQUEST_ID): cv.use_id(cv.Any()),
    }).extend(cv.COMPONENT_SCHEMA),
    cv.only_on(["esp32"]),
)

@coroutine_with_priority(40.0)
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_url(config[CONF_INFLUXDB_URL]))
    cg.add(var.set_token(config[CONF_INFLUXDB_TOKEN]))
    cg.add(var.set_org(config[CONF_INFLUXDB_ORG]))
    cg.add(var.set_bucket(config[CONF_INFLUXDB_BUCKET]))
    cg.add(var.set_measurement(config[CONF_INFLUXDB_MEASUREMENT]))

    http = await cg.get_variable(config[CONF_HTTP_REQUEST_ID])
    cg.add(var.set_http(http))
