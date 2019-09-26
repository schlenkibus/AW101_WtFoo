#pragma once
#include "BangModule.h"
#include "ClockModule.h"
#include "DuplicationModule.h"
#include "NumberModule.h"
#include "SineOscillatorModule.h"

class BasicModules {
private:
  template <class module>
  static void registerHelper(const char *name, DSPHost *host) {
    host->registerModule(name, [](DSPHost *host) { return new module(host); });
  }

public:
  static void registerModules(DSPHost *host) {
    registerHelper<BangModule>("BangModule", host);
    registerHelper<ClockModule>("ClockModule", host);
    registerHelper<DuplicationModule>("DuplicationModule", host);
    registerHelper<NumberModule>("NumberModule", host);
    registerHelper<SineOscillatorModule>("SineOscillatorModule", host);
  }
};