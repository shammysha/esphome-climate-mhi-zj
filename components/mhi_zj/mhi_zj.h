#pragma once

#include "esphome/components/climate_ir/climate_ir.h"
#include <cinttypes>

namespace esphome {
namespace mhi_zj {
// Temperature
const uint8_t MHI_TEMP_MIN = 18;  // Celsius
const uint8_t MHI_TEMP_MAX = 30;  // Celsius

// Enum to represent horizontal directios
enum HorizontalDirection {
  MHI_HS_SWING = 0x4C,
  MHI_HS_MIDDLE = 0x48,
  MHI_HS_LEFT = 0xC8,
  MHI_HS_MLEFT = 0x88,
  MHI_HS_MRIGHT = 0x08,
  MHI_HS_RIGHT = 0xC4,
  MHI_HS_STOP = 0xCC,
  MHI_HS_LEFTRIGHT = 0x84,
  MHI_HS_RIGHTLEFT = 0x44,
  MHI_HS_3DAUTO = 0x04,
};

// Enum to represent vertical directions
enum VerticalDirection {
  MHI_VS_SWING = 0x0A,
  MHI_VS_UP = 0x02,
  MHI_VS_MUP = 0x18,
  MHI_VS_MIDDLE = 0x10,
  MHI_VS_MDOWN = 0x08,
  MHI_VS_DOWN = 0x00,
  MHI_VS_STOP = 0x1A,
};


class MhiClimate : public climate_ir::ClimateIR {
 public:
  MhiClimate()
      : climate_ir::ClimateIR(
            MHI_TEMP_MIN, MHI_TEMP_MAX, 1.0f, true, true,
            std::set<climate::ClimateFanMode>{climate::CLIMATE_FAN_AUTO, climate::CLIMATE_FAN_LOW,
                                              climate::CLIMATE_FAN_MEDIUM, climate::CLIMATE_FAN_HIGH,
                                              climate::CLIMATE_FAN_MIDDLE, climate::CLIMATE_FAN_FOCUS,
                                              climate::CLIMATE_FAN_DIFFUSE},
            std::set<climate::ClimateSwingMode>{climate::CLIMATE_SWING_OFF, climate::CLIMATE_SWING_VERTICAL,
                                                climate::CLIMATE_SWING_HORIZONTAL, climate::CLIMATE_SWING_BOTH}) {}

  void set_horizontal_default(HorizontalDirection horizontal_direction) {
    this->default_horizontal_direction_ = horizontal_direction;
  }
  void set_vertical_default(VerticalDirection vertical_direction) {
    this->default_vertical_direction_ = vertical_direction;
  }

 protected:
  void transmit_state() override;
  /// Handle received IR Buffer
  bool on_receive(remote_base::RemoteReceiveData data) override;

  HorizontalDirection default_horizontal_direction_;
  VerticalDirection default_vertical_direction_;

  climate::ClimateTraits traits() override;
};
}  // namespace mhi_zj
}  // namespace esphome
