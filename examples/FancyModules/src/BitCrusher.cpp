#include <cmath>
#include "BitCrusher.h"

BitCrusher::BitCrusher(DSPHost* host)
    : DSPModule(host)
{
  m_out = createOutput("Output");
  m_in = createInput("Input");
  m_bitDepth = createParameter("Bit Depth", 32, 1, 32, 0);
}

const char* BitCrusher::getName()
{
  return nullptr;
}

long crushBits(const float val, const uint8_t bit_depth)
{
  if (val >= 1.0) return std::pow(2, bit_depth-1) - 1;
  else if (val <= -1.0) return std::pow(-2, bit_depth-1);
  else return std::floor( val * -std::pow(-2, bit_depth-1) );
}

float crushedBitToFloat(const long val, const uint8_t bit_depth)
{
  return val / -powf(-2, bit_depth-1);
}

void BitCrusher::tick()
{
  DSPContainer::tick();

  if(m_bits != static_cast<short>(m_bitDepth->getValue()))
  {
    m_bits = static_cast<short>(m_bitDepth->getValue());
  }

  m_out->set(crushedBitToFloat(crushBits(m_in->getSignal(), m_bits), m_bits));
}
