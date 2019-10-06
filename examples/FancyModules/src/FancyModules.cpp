#include "ADSREnvelope.h"
#include "CrossFaderModule.h"
#include "RandomModule.h"
#include "SequencerModule.h"
#include "SmootherModule.h"

extern "C" {
void DSPPlugin_registerModule(DSPHost *h) {
    h->registerModule(std::string("SequencerModule").c_str(),
                      [](DSPHost *h) { return new SequencerModule(h); });
    h->registerModule(std::string("RandomModule").c_str(),
                      [](DSPHost *h) { return new RandomModule(h); });
    h->registerModule(std::string("SmootherModule").c_str(),
                      [](DSPHost *h) { return new SmootherModule(h); });
    h->registerModule(std::string("CrossFaderModule").c_str(),
        [](DSPHost* h) { return new CrossFaderModule(h);});
    h->registerModule(std::string("ADSREnvelope").c_str(),
            [](DSPHost *h) { return new ADSREnvelope(h); });
}
}
