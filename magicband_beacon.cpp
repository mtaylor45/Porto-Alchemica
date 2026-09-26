#include "magicband_beacon.h"

#ifdef USE_ESP32

#include "esphome/core/log.h"
#include <esp_bt.h>

namespace esphome {
namespace magicband_beacon {

static const char *const TAG = "magicband_beacon";

void MagicBandBeacon::setup() {
  // Range is the geofence. Turning power down keeps the burst inside
  // the room / porch instead of buzzing every band in the house.
  esp_ble_tx_power_set(ESP_PWR_TYPE_ADV, (esp_power_level_t) this->tx_power_);
  ESP_LOGCONFIG(TAG, "MagicBand beacon ready");
}

void MagicBandBeacon::dump_config() {
  ESP_LOGCONFIG(TAG, "MagicBand Beacon:");
  ESP_LOGCONFIG(TAG, "  TX power level: %d", this->tx_power_);
}

void MagicBandBeacon::send_burst(const std::vector<uint8_t> &payload, uint32_t duration_ms,
                                 uint16_t interval) {
  if (payload.empty() || payload.size() > 26) {
    ESP_LOGW(TAG, "Payload must be 1-26 bytes, got %d", (int) payload.size());
    return;
  }

  // AD structure: [length][0xFF manufacturer specific][company LE][payload]
  std::vector<uint8_t> adv;
  adv.push_back(payload.size() + 3);
  adv.push_back(0xFF);
  adv.push_back(COMPANY_ID_LO);
  adv.push_back(COMPANY_ID_HI);
  adv.insert(adv.end(), payload.begin(), payload.end());

  esp_err_t err = esp_ble_gap_config_adv_data_raw(adv.data(), adv.size());
  if (err != ESP_OK) {
    ESP_LOGW(TAG, "config_adv_data_raw failed: %d", err);
    return;
  }

  esp_ble_adv_params_t params{};
  params.adv_int_min = interval;
  params.adv_int_max = interval;
  params.adv_type = ADV_TYPE_NONCONN_IND;  // broadcast only, nothing connects
  params.own_addr_type = BLE_ADDR_TYPE_RANDOM;
  params.channel_map = ADV_CHNL_ALL;
  params.adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY;

  err = esp_ble_gap_start_advertising(&params);
  if (err != ESP_OK) {
    ESP_LOGW(TAG, "start_advertising failed: %d", err);
    return;
  }

  this->advertising_ = true;
  ESP_LOGD(TAG, "Broadcasting %d bytes for %ums", (int) payload.size(), duration_ms);

  this->cancel_timeout("burst");
  this->set_timeout("burst", duration_ms, [this]() { this->stop_advertising_(); });
}

void MagicBandBeacon::stop_advertising_() {
  if (!this->advertising_)
    return;
  esp_ble_gap_stop_advertising();
  this->advertising_ = false;
  ESP_LOGD(TAG, "Burst finished");
}

}  // namespace magicband_beacon
}  // namespace esphome

#endif  // USE_ESP32
