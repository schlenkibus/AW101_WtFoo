#pragma once
#include "AudioOutModule.h"
#include "MixerModule.h"
#include "MathModule.h"

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
  }
};