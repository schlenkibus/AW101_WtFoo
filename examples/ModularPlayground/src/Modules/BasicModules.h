#pragma once
#include <libDSP/include/DSPHost.h>
#include <WaveTables.h>
#include "AudioOutModule.h"
#include "MixerModule.h"
#include "MathModule.h"
#include "WaveTableOscillator.h"

class BasicModules
{
 private:
  template <class module> static void registerModule(const char *name, DSPHost *host)
  {
    host->registerModule(name, [](DSPHost *host) { return new module(host); });
  }

  template <typename T> static void registerMathModule(const char *name, DSPHost *host, T t)
  {
    host->registerModule(name, [=](DSPHost *host) { return new MathModule(name, host, t); });
  }

 public:
  static void registerModules(DSPHost *host)
  {
    registerModule<MixerModule>("MixerModule", host);
    registerModule<AudioOutModule>("AudioOutModule", host);
    registerMathModule("Plus", host, [](auto x, auto y) { return x + y; });
    registerMathModule("Minus", host, [](auto x, auto y) { return x - y; });
    registerMathModule("Multiply", host, [](auto x, auto y) { return x * y; });
    registerMathModule("Divide", host, [](auto x, auto y) { return x / y; });
    host->registerModule("sine-oscillator",
                         [](DSPHost *h) { return new WaveTableOscillator<SineWaveTable<44100>>(h); });
    host->registerModule("triangle-oscillator",
                         [](DSPHost *h) { return new WaveTableOscillator<TriangleWaveTable<44100>>(h); });
    host->registerModule("saw-oscillator", [](DSPHost *h) { return new WaveTableOscillator<SawWaveTable<44100>>(h); });
  }
};