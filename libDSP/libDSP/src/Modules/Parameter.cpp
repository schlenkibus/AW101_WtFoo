#include <utility>
#include "../../include/Modules/Parameter.h"

Parameter::Parameter(std::string n, float min, float max,
                     float init, int pre) : value{init}, name{std::move(n)}, m_max{max}, m_min{min}, m_precision{pre} {}

void Parameter::setValue(float v) {
  value = std::min(m_max, std::max(m_min, v));
}

float Parameter::getValue() const {
  return value;
}
