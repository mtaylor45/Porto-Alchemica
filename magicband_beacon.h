#pragma once

#ifdef USE_ESP32

#include <vector>
#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include <esp_gap_ble_api.h>

namespace esphome {
namespace magicband_beacon {

// Disney's BLE company identifier as entered in nRF Connect: 0183.
// On air, company ID is little-endian, so the bytes are 0x83 0x01.
// If your bands do not respond, try swapping these two -- community
// captures disagree about which order the published codes assume.
static const uint8_t COMPANY_ID_LO = 0x83;
static const uint8_t COMPANY_ID_HI = 0x01;

class MagicBandBeacon : public Component {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::AFTER_BLUETOOTH; }

  void set_tx_power(int level) { this->tx_power_ = level; }

  // Broadcast `payload` as manufacturer data for `duration_ms`.
  void send_burst(const std::vector<uint8_t> &payload, uint32_t duration_ms, uint16_t interval);

 protected:
  void stop_advertising_();
  int tx_power_{0};
  bool advertising_{false};
};

template<typename... Ts> class SendAction : public Action<Ts...> {
 public:
  explicit SendAction(MagicBandBeacon *parent) : parent_(parent) {}

  void set_payload(const std::vector<uint8_t> &payload) { this->payload_ = payload; }
  void set_duration(uint32_t duration) { this->duration_ = duration; }
  void set_interval(uint16_t interval) { this->interval_ = interval; }

  void play(Ts... x) override {
    this->parent_->send_burst(this->payload_, this->duration_, this->interval_);
  }

 protected:
  MagicBandBeacon *parent_;
  std::vector<uint8_t> payload_;
  uint32_t duration_{3000};
  uint16_t interval_{32};
};

}  // namespace magicband_beacon
}  // namespace esphome

#endif  // USE_ESP32
