import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import esp32_ble
from esphome.const import CONF_ID

DEPENDENCIES = ["esp32", "esp32_ble"]
AUTO_LOAD = ["esp32_ble"]

magicband_ns = cg.esphome_ns.namespace("magicband_beacon")
MagicBandBeacon = magicband_ns.class_("MagicBandBeacon", cg.Component)
SendAction = magicband_ns.class_("SendAction", automation.Action)

CONF_TX_POWER = "tx_power"
CONF_PAYLOAD = "payload"
CONF_DURATION = "duration"
CONF_INTERVAL = "interval"

# Lower dBm = shorter reach = tighter "geofence".
TX_POWER_LEVELS = {
    -12: 0, -9: 1, -6: 2, -3: 3, 0: 4, 3: 5, 6: 6, 9: 7,
}

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(MagicBandBeacon),
    cv.Optional(CONF_TX_POWER, default=-12): cv.enum(TX_POWER_LEVELS, int=True),
}).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cg.add(var.set_tx_power(config[CONF_TX_POWER]))


@automation.register_action(
    "magicband_beacon.send",
    SendAction,
    cv.Schema({
        cv.GenerateID(): cv.use_id(MagicBandBeacon),
        # Hex string of the command bytes that follow the company ID.
        cv.Required(CONF_PAYLOAD): cv.string,
        # How long to keep broadcasting. The band's scan window is
        # intermittent, so one packet is not enough.
        cv.Optional(CONF_DURATION, default="3s"): cv.positive_time_period_milliseconds,
        # Advertising interval in 0.625ms units. 32 = 20ms (the minimum).
        cv.Optional(CONF_INTERVAL, default=32): cv.int_range(min=32, max=16384),
    }),
)
async def send_action_to_code(config, action_id, template_arg, args):
    parent = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, parent)
    payload = bytes.fromhex(config[CONF_PAYLOAD].replace(" ", "").replace(":", ""))
    cg.add(var.set_payload(list(payload)))
    cg.add(var.set_duration(config[CONF_DURATION]))
    cg.add(var.set_interval(config[CONF_INTERVAL]))
    return var
