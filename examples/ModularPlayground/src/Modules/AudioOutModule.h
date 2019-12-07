#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class AudioOutModule : public DSPModule
{
 public:
  explicit AudioOutModule(DSPHost *parent);
  DSPInputNode *leftChannel();
  DSPInputNode *rightChannel();
  Parameter *getMasterGain();
const char * getTypeName() const override;

 private:
  DSPInputNode *m_left = nullptr;
  DSPInputNode *m_right = nullptr;
  Parameter *m_master = nullptr;
};
