#include "SliderWithLabel.h"
#include <cmath>
#include <iomanip>

SliderWithLabel::SliderWithLabel(const std::string &name, float min, float max,
                                 int precision)
    : m_min{min}, m_max{max}, m_precision{precision} {
  m_header = addWidget(std::make_unique<Wt::WLabel>());
  m_header->setText(name);

  m_slider = addWidget(std::make_unique<Wt::WSlider>());
  m_slider->setNativeControl(true);
  m_slider->setStyleClass("custom-slider");

  m_factor = std::pow(10, m_precision);

  m_slider->setRange(m_min * m_factor, m_max * m_factor);
  m_slider->changed().connect(this, &SliderWithLabel::onSliderMoved);
  m_valueText = addWidget(std::make_unique<Wt::WLabel>());
}

std::string SliderWithLabel::toDisplayString() const {
  std::stringstream ss;
  ss << m_currentValue;
  return ss.str();
}

void SliderWithLabel::onSliderMoved() {
  auto value = m_slider->value();
  m_currentValue = static_cast<float>(value) / m_factor;

  m_valueText->setText(toDisplayString());
  onSliderChanged(m_currentValue);
}
