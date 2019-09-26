#pragma once
#include <libDSP/include/DSPHost.h>
#include <libDSP/include/Modules/DSPModule.h>

class RandomModule : public DSPModule {
public:
  explicit RandomModule(DSPHost *parent);
  const char *TYPE() const override;
  void tick() override;

private:
  std::array<double, 10000> m_cachedRandomness{};
  size_t m_readHead = 0;
  Input* m_tick;
  Output* m_out;
  Parameter* m_range;

  bool waitingForDown = false;
};

extern "C" {
  void DSPPlugin_registerModule(DSPHost* h) {
    h->registerModule(std::string("RandomModule").c_str(), [](DSPHost* h) { return new RandomModule(h); });
  }
}