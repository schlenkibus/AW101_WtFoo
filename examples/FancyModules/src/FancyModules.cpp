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
}
}
