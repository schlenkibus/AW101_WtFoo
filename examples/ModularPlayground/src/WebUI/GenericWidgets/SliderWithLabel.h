#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>
#include <Wt/WSlider.h>

class SliderWithLabel : public Wt::WContainerWidget {
public:
  explicit SliderWithLabel(const std::string &name, float min, float max,
                           int precision = 3);
  virtual void onSliderChanged(float value) = 0;

private:
  virtual std::string toDisplayString() const;
  float m_currentValue{0.0};
  float m_min = -1.0;
  float m_max = 1.0;

  int m_precision;

  void onSliderMoved();

protected:
  Wt::WLabel *m_header;
  Wt::WLabel *m_valueText;
  Wt::WSlider *m_slider;
};
