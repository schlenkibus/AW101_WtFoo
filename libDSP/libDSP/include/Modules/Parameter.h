#pragma once
#include <string>

class Parameter
{
 public:
  Parameter(std::string n, float min, float max, float init, int pre = 3);
  std::string name;
  void setValue(float v);
  float getValue() const;

  void setToDefault();

  const float m_min;
  const float m_max;

  int m_precision;

 private:
  const float m_default;
  float value;
};