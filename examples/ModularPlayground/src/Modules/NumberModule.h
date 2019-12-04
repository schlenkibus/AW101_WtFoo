#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class NumberModule : public DSPModule
{
 public:
  explicit NumberModule(DSPHost* host);
  const char* getTypeName() const override;
  void tickInternals() override;
  void setNumber(float number);

 private:
  float m_number { 0.0 };
  DSPOutputNode* m_out { nullptr };
};
