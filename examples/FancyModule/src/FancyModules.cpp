#include "RandomModule.h"

extern "C" {
  void DSPPlugin_registerModule(DSPHost *h) {
    h->registerModule(std::string("RandomModule").c_str(),
                      [](DSPHost *h) { return new RandomModule(h); });
  }
}
