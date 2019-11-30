#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class MixerModule : public DSPModule
{
 public:
  MixerModule(DSPHost *parent);
  void tickInternals() override;
  DSPOutputNode *m_out;
};
