#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class BitCrusher : public DSPModule
{
 public:
  BitCrusher(DSPHost* host);
  void tick() override;

 private:
  Output* m_out;
  Input* m_in;
  Parameter* m_bitDepth;

  short m_bits = 32;
};
