#include "ParameterSlider.h"
#include <cmath>

ParameterSlider::ParameterSlider(tCB cb, const std::string &name, float min,
                                 float max, int precision, float init)
    : SliderWithLabel(name, min, max, precision), m_cb{std::move(cb)} {
  m_slider->setValue(init * std::pow(10, precision));
}

void ParameterSlider::onSliderChanged(float value) {
  m_cb(value);
}
