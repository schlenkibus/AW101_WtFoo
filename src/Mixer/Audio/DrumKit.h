#pragma once
#include "../../LibDSP/DSPNodes/DSPNode.h"
#include "../../Nodes/ADREnvelope.h"
#include "../../Nodes/WaveTableOscillator.h"

class DrumKit : public DSPNode {
public:
    DrumKit();
    void reset() override;
    void tick() override;
    void hit();

    ADREnvelope m_pitchEnvelope;
    ADREnvelope m_ampEnvelope;
    WaveTableOscillator<TemplateSineWaveTable<2048>> m_osc;
    float startFreq = 0.0;
};
