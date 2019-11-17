#include "ParameterSlider.h"
#include <cmath>
#include <libDSP/include/Modules/Parameter.h>
#include "Wt/WPushButton.h"

ParameterSlider::ParameterSlider(Parameter *parameter)
    : SliderWithLabel(parameter->name, parameter->m_min, parameter->m_max, parameter->m_precision), m_parameter{parameter} {
  m_slider->setValue(m_parameter->getValue() * std::pow(10, m_parameter->m_precision));
  onSliderChanged(m_parameter->getValue());
  setStyleClass("parameter-container");

  m_default = addWidget(std::make_unique<Wt::WPushButton>());
  m_default->clicked().connect([this]() {
      m_parameter->setToDefault();
  });
  m_default->setText("Default");
}

void ParameterSlider::onSliderChanged(float value) {
  m_parameter->setValue(value);
}
