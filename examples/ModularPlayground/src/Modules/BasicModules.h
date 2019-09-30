#pragma once
#include "AdditionModule.h"
#include "ClockModule.h"
#include "DuplicationModule.h"
#include "MixerModule.h"
#include "MultiplicationModule.h"
#include "NegationModule.h"
#include "NumberModule.h"
#include "RampModule.h"
#include "SineOscillatorModule.h"

class BasicModules {
private:
  template <class module>
  static void registerHelper(const char *name, DSPHost *host) {
    host->registerModule(name, [](DSPHost *host) { return new module(host); });
  }

public:
  static void registerModules(DSPHost *host) {
    registerHelper<ClockModule>("ClockModule", host);
    registerHelper<DuplicationModule>("DuplicationModule", host);
    registerHelper<NumberModule>("NumberModule", host);
    registerHelper<SineOscillatorModule>("SineOscillatorModule", host);
    registerHelper<MultiplicationModule>("MultiplicationModule", host);
    registerHelper<NegationModule>("NegationModule", host);
    registerHelper<RampModule>("RampModule", host);
    registerHelper<MixerModule>("MixerModule", host);
    registerHelper<AdditionModule>("AdditionModule", host);
  }
};