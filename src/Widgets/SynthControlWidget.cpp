#include <Wt/WPushButton.h>
#include <Wt/WSlider.h>

#include "ParameterPack.h"
#include "SampleInspectorWidget.h"
#include "SynthControlWidget.h"
SynthControlWidget::SynthControlWidget(MySynthesizer &synthesizer) : m_synth{synthesizer} {

  m_sampleInspector = addWidget(std::make_unique<SampleInspectorWidget>(m_synth));

  auto attack = addWidget(std::make_unique<ParameterPack>("Attack Value", 0, 100, [this](auto rawValue) {
    m_synth.setAttackValue(rawValue / 100.0);
  }));

  auto decay = addWidget(std::make_unique<ParameterPack>("Decay Value", 0, 100, [this](auto rawValue) {
    m_synth.setDecayValue(rawValue / 100.0);
  }));

  auto attackTime = addWidget(std::make_unique<ParameterPack>("Attack Time", 0, 5000, [this](auto rawValue) {
    m_synth.setAttackTime((rawValue / 1000.0f) * DSPInfo::SampleRate);
  }, [](auto value) {
    return std::to_string(value / 1000.0f) + "s";
  }));

  auto decayTime = addWidget(std::make_unique<ParameterPack>("Decay Time", 0, 5000, [this](auto rawValue) {
    m_synth.setDecayTime((rawValue / 1000.0f) * DSPInfo::SampleRate);
  }, [](auto value) {
    return std::to_string(value / 1000.0f) + "s";
  }));

  auto releaseTime = addWidget(std::make_unique<ParameterPack>("Release Time", 0, 5000, [this](auto rawValue) {
    m_synth.setReleaseTime((rawValue / 1000.0f) * DSPInfo::SampleRate);
  }, [](auto value) {
    return std::to_string(value / 1000.0f) + "s";
  }));

  auto masterKey = addWidget(std::make_unique<ParameterPack>("Master Key", -100, 100, [this](auto rawValue) {
    m_synth.setMasterKey(rawValue);
  }));

  auto oscIOffset = addWidget(std::make_unique<ParameterPack>("OSC I Phaseoffset", 0, 500, [this](auto rawValue) {
    m_synth.setPhaseOffset(rawValue / 1000.0);
  }, [](auto value) {
    auto toPi = value / 1000.0;
    return std::to_string(toPi);
  }));

  for(auto v: {90, 100, 110, 120, 130, 140, 150}) {
    auto b = addWidget(std::make_unique<Wt::WPushButton>());
    b->setText(std::to_string(v));
    b->clicked().connect([this, v]() {
      m_synth.addNote(v);
    });
  }

  for(const std::pair<int, int> c: std::vector<std::pair<int, int>>{{90, 150}, {100, 160}}) {
    auto b = addWidget(std::make_unique<Wt::WPushButton>());
    b->setText(std::to_string(c.first) + " + " + std::to_string(c.second));
    b->clicked().connect([this, c]() {
      m_synth.addNote(c.first);
      m_synth.addNote(c.second);
    });
  }
}
SampleInspectorWidget *SynthControlWidget::getSampleInspector() {
  return m_sampleInspector;
}
