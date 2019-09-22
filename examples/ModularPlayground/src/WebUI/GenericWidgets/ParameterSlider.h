#pragma once
#include "SliderWithLabel.h"
#include <libDSP/include/Modules/Parameter.h>

class ParameterSlider : public SliderWithLabel {
public:
  using tCB = std::function<void(float)>;
  explicit ParameterSlider(Parameter *parameter);
  void onSliderChanged(float value) override;

private:
  Parameter* m_parameter;
};
