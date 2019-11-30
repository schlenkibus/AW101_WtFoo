#pragma once
#include "AudioOutModule.h"
#include "MixerModule.h"

class BasicModules
{
 private:
  template <class module> static void registerHelper(const char *name, DSPHost *host)
  {
    host->registerModule(name, [](DSPHost *host) { return new module(host); });
  }

  template <typename OSC> static void registerOscillator(const char *name, DSPHost *host)
  {
    host->registerModule(name, [name](DSPHost *host) { return new OSC(host, name); });
  }

 public:
  static void registerModules(DSPHost *host)
  {
    registerHelper<MixerModule>("MixerModule", host);
    registerHelper<AudioOutModule>("AudioOutModule", host);
  }
};