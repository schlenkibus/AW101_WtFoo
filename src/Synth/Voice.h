#pragma once

#include "DSPNodes/ADREnvelope.h"
#include "DSPNodes/DSPNode.h"
#include "DSPNodes/SineWaveGenerator.h"

class MySynthesizer;

class Voice : public DSPNode {
public:


  void noteOn(int key, float velocity);
  void noteOff();
  void tick() override;
  void reset() override;


  int key;
protected:
  SineWaveGenerator<TemplateSineWaveTable<4096>> m_oscillatorI;
  SineWaveGenerator<TemplateSineWaveTable<4096>> m_oscillatorII;
  ADREnvelope m_envelope;


  friend class MySynthesizer;
};