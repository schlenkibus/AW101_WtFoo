#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class MixerModule : public DSPModule {
public:
  MixerModule(DSPHost *parent);
  void tick() override;
  Output *m_out;
};
