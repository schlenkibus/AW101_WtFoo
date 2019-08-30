#include <Wt/WPushButton.h>
#include <Wt/WSlider.h>
#include <Wt/WCssDecorationStyle.h>


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

  auto sustain = addWidget(std::make_unique<ParameterPack>("Sustain Value", 0, 100, [this](auto rawValue) {
    m_synth.setSustainValue(rawValue / 100.0);
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

  auto susTime = addWidget(std::make_unique<ParameterPack>("Sustain Fluc", 1, DSPInfo::SampleRate * 10, [this](auto rawValue) {
    DSPInfo::Envelope::TransitionTime = rawValue;
  }, [](auto val) {
    return std::to_string(static_cast<float>(val) / DSPInfo::SampleRate) + "s";
  }));

  auto exciter = addWidget(std::make_unique<ParameterPack>("Sustain Exciter", 0, 100, [this](auto rawValue) {
    float val = rawValue / 100.0;
    val -= 0.5;
    DSPInfo::Envelope::Exciter = val;
  }, [](auto rawValue) {
    float val = rawValue - 50;
    return std::to_string(val) + "%";
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
    auto* b = addWidget(std::make_unique<Wt::WPushButton>());
    b->setText(std::to_string(v));
    b->clicked().connect([this, v, b]() {
      auto onOff = m_synth.toggleNote(v);
      Wt::WColor color;
      color.setRgb(onOff ? 255 : 0, onOff ? 0 : 255, 0);
      b->decorationStyle().setBackgroundColor(color);
    });
  }

}
SampleInspectorWidget *SynthControlWidget::getSampleInspector() {
  return m_sampleInspector;
}
