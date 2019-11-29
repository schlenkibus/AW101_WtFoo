#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class AudioOutModule : public DSPModule {
public:
  explicit AudioOutModule(DSPHost *parent);
  Input *leftChannel();
  Input *rightChannel();
  Parameter *getMasterGain();

private:
  Input *m_left = nullptr;
  Input *m_right = nullptr;
  Parameter *m_master = nullptr;
};
