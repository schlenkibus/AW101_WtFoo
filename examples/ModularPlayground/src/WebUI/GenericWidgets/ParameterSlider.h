#pragma once
#include "SliderWithLabel.h"

class ParameterSlider : public SliderWithLabel {
public:
  using tCB = std::function<void(float)>;
  explicit ParameterSlider(tCB cb, const std::string &name, float min,
                           float max, int precision, float init);
  void onSliderChanged(float value) override;

private:
  tCB m_cb;
};
