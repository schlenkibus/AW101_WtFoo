#include "FancyModules.h"
#include "SequencerModule.h"
#include "BPMBeepBoop.h"
#include <libDSP/include/DSPHost.h>

extern "C"
{
  void DSPPlugin_registerModule(DSPHost *h)
  {
    h->registerModule("SequencerModule", [](DSPHost *h) { return new SequencerModule(h); });
    h->registerModule("BPMBeepBoop", [](DSPHost *h) { return new BPMBeepBoop(h); });
  }
}