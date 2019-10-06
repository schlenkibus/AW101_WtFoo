#pragma once
#include <libDSP/include/DSPHost.h>
#include <libDSP/include/Modules/DSPModule.h>

class RandomModule : public DSPModule {
public:
  explicit RandomModule(DSPHost *parent);
  void tick() override;
const char * getName() override;

private:
  std::array<double, 10000> m_cachedRandomness{};
  size_t m_readHead = 0;
  Input* m_tick;
  Output* m_out;
  Input* m_range;

  bool waitingForDown = false;
};