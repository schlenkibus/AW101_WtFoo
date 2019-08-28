#pragma once

#include "DSPNodes/DSPNode.h"
#include "DSPNodes/DSPOutputNode.h"
#include "OutputMixer.h"
#include "RingBuffer.h"
#include "Voice.h"
#include <chrono>
#include <functional>
#include <memory>
#include <portaudio.h>

class MySynthesizer {
public:
    using tRingBuffer = RingBuffer<float, DSPInfo::SampleRate / 50>;
    MySynthesizer(int sampleRate, int framesPerBuffer);
    void tick();

    void addNote(int key, float velocity = -1.0);

    float getOutputMixerLeft() const;
    float getOutputMixerRight() const;

    void setAttackValue(float value);
    void setDecayValue(float value);

    void setAttackTime(long ticks);
    void setDecayTime(long ticks);
    void setReleaseTime(long ticks);
    void setMasterKey(int key);
    void setPhaseOffset(float offset);
    tRingBuffer& getRingBuffer();


protected:
    PaStream *m_stream;

    std::array<Voice, 5> m_voices;
    tRingBuffer m_ringbuffer;

    float m_velocity = 1.0;
    int m_masterKey = 30;

    float _signal;

    friend class SynthControlWidget;
};
