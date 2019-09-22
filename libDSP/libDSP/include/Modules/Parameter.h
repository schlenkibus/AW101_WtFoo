#pragma once
#include <string>

class Parameter {
public:
  Parameter(std::string n, float min, float max, float init);
  std::string name;
  void setValue(float v);
  float getValue() const;

  const float m_min;
  const float m_max;

private:
  float value;
};