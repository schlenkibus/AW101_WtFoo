#pragma once
#include "AdditionModule.h"
#include "AudioOutModule.h"
#include "ClockModule.h"
#include "DuplicationModule.h"
#include "MixerModule.h"
#include "MultiplicationModule.h"
#include "NegationModule.h"
#include "NumberModule.h"
#include "OscillatorModule.h"
#include "RampModule.h"

class BasicModules {
private:
  template <class module>
  static void registerHelper(const char *name, DSPHost *host) {
    host->registerModule(name, [](DSPHost *host) { return new module(host); });
  }

  template <typename OSC>
  static void registerOscillator(const char *name, DSPHost *host) {
    host->registerModule(name,
                         [name](DSPHost *host) { return new OSC(host, name); });
  }

public:
  static void registerModules(DSPHost *host) {
    registerHelper<DuplicationModule>("DuplicationModule", host);
    registerHelper<NumberModule>("NumberModule", host);
    registerHelper<MultiplicationModule>("MultiplicationModule", host);
    registerHelper<NegationModule>("NegationModule", host);
    registerHelper<RampModule>("RampModule", host);
    registerHelper<MixerModule>("MixerModule", host);
    registerHelper<AdditionModule>("AdditionModule", host);
    registerHelper<AudioOutModule>("AudioOutModule", host);

    host->registerModule("ClockModuleFast", [](DSPHost *host) {
      return new ClockModule(host, false);
    });
    host->registerModule("ClockModuleSlow", [](DSPHost *host) {
      return new ClockModule(host, true);
    });

    host->registerModule("AlternatingClock", [](DSPHost *host) {
      return new AlternatingClock(host);
    });

    registerOscillator<
        OscillatorModule<WaveTableOscillator<SineWaveTable<2048>>>>(
        "SineWaveTableOscillator", host);
    registerOscillator<
        OscillatorModule<WaveTableOscillator<SineWaveTable<8192>>>>(
        "SineWaveTableOscillatorHQ", host);
    registerOscillator<
        OscillatorModule<WaveTableOscillator<SawWaveTable<2048>>>>(
        "SawWaveTableOsciilator", host);
    registerOscillator<
        OscillatorModule<WaveTableOscillator<SawWaveTable<8192>>>>(
        "SawWaveTableOsciilatorHQ", host);
    registerOscillator<
        OscillatorModule<WaveTableOscillator<TriangleWaveTable<2048>>>>(
        "TriangleWaveTableOsciilator", host);
    registerOscillator<
        OscillatorModule<WaveTableOscillator<TriangleWaveTable<8192>>>>(
        "TriangleWaveTableOsciilatorHQ", host);
  }
};