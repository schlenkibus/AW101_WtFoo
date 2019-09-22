#include <utility>

#include "../../include/Modules/Parameter.h"

Parameter::Parameter(std::string n, float min, float max,
                     float init) : value{init}, name{std::move(n)}, m_max{max}, m_min{min} {}

void Parameter::setValue(float v) {
  value = std::min(m_max, std::max(m_min, v));
}

float Parameter::getValue() const {
  return value;
}
