#pragma once
#include "../../Synth/DSPNodes/ADREnvelope.h"
#include "../../Synth/DSPNodes/SineWaveGenerator.h"

class DrumKit {
public:
    DrumKit();
    void tick();
    void hit();


    double _signal;

    ADREnvelope m_pitchEnvelope;
    ADREnvelope m_ampEnvelope;
    SineWaveGenerator<TemplateSineWaveTable<2048>> m_osc;
    float startFreq = 0.0;
};
