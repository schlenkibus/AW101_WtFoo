#include "ADSREnvelope.h"
#include "CrossFaderModule.h"
#include "RandomModule.h"
#include "SequencerModule.h"
#include "SmootherModule.h"
#include "BPMBeepBoop.h"
#include "LowPassFilter.h"

extern "C"
{
  void DSPPlugin_registerModule(DSPHost *h)
  {
    h->registerModule("SequencerModule", [](DSPHost *h) { return new SequencerModule(h); });
    h->registerModule("RandomModule", [](DSPHost *h) { return new RandomModule(h); });
    h->registerModule("SmootherModule", [](DSPHost *h) { return new SmootherModule(h); });
    h->registerModule("CrossFaderModule", [](DSPHost *h) { return new CrossFaderModule(h); });
    h->registerModule("ADSREnvelope", [](DSPHost *h) { return new ADSREnvelope(h); });
    h->registerModule("BPMBeepBoop", [](DSPHost *h) { return new BPMBeepBoop(h); });
    h->registerModule("LPF", [](DSPHost *h) { return new LowPassFilter(h); });
  }
}
