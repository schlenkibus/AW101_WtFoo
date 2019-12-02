#pragma once
#include <libDSP/include/Modules/DSPModule.h>
#include <atomic>

class ButtonModule : public DSPModule
{
 public:
  explicit ButtonModule(DSPHost* parent);
  void tickInternals() override;
  void setState(bool s);
  const char* getTypeName() const override;

 private:
  std::atomic_bool m_active { false };
  DSPOutputNode* m_out;
};