#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class AudioOutModule : public DSPModule {
public:
  explicit AudioOutModule(DSPHost *parent);
  const char *getName() override;
  Input *leftChannel();
  Input *rightChannel();

private:
  Input *m_left = nullptr;
  Input *m_right = nullptr;
};
