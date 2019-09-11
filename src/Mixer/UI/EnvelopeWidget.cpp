#include "EnvelopeWidget.h"
#include "../../Synth/DSPInfo.h"
#include "../../Widgets/ParameterPack.h"

EnvelopeWidget::EnvelopeWidget(ADREnvelope &envelope,
                               const std::string &baseName)
    : m_envelope{envelope} {
  auto pitchAttack = addWidget(std::make_unique<ParameterPack>(
      baseName + " Envelope Attack Time", 1, 500,
      [this](auto value) {
        m_envelope.setLength<ADREnvelope::State::Attack>(DSPInfo::SampleRate *
                                                         (value / 1000.0));
      },
      [](auto value) {
        std::stringstream ss;
        ss.precision(3);
        ss << std::fixed << value / 1000.0 << " S";
        return ss.str();
      }));

  pitchAttack->initializeSlider((m_envelope.getLength<ADREnvelope::State::Attack>() * 1000.0) / DSPInfo::SampleRate);

  auto pitchDecay = addWidget(std::make_unique<ParameterPack>(
      baseName + " Envelope Decay Time", 1, 500,
      [this](auto value) {
        m_envelope.setLength<ADREnvelope::State::Decay>(DSPInfo::SampleRate *
                                                        (value / 1000.0));
      },
      [](auto value) {
        std::stringstream ss;
        ss.precision(3);
        ss << std::fixed << value / 1000.0 << " S";
        return ss.str();
      }));
  pitchDecay->initializeSlider((m_envelope.getLength<ADREnvelope::State::Decay>() * 1000.0) / DSPInfo::SampleRate);


  auto pitchRelease = addWidget(std::make_unique<ParameterPack>(
      baseName + " Envelope Release Time", 1, 1000, [this](auto value) {
        m_envelope.setLength<ADREnvelope::State::Release>(DSPInfo::SampleRate *
                                                          (value / 1000.0));
      },
      [](auto value) {
        std::stringstream ss;
        ss.precision(3);
        ss << std::fixed << value / 1000.0 << " S";
        return ss.str();
      }));
  pitchRelease->initializeSlider((m_envelope.getLength<ADREnvelope::State::Release>() * 1000.0) / DSPInfo::SampleRate);


  auto attackVal = addWidget(std::make_unique<ParameterPack>(
      baseName + " Envelope Attack Value", 10, 1000, [this](auto value) {
        m_envelope.setValue<ADREnvelope::State::Attack>(value / 1000.0);
      },
      [](auto value) {
        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << value / 1000.0 << "%";
        return ss.str();
      }));
  attackVal->initializeSlider((m_envelope.getLevel<ADREnvelope::State::Attack>() * 1000.0));


  auto DecayVal = addWidget(std::make_unique<ParameterPack>(
      baseName + " Envelope Decay Value", 10, 1000, [this](auto value) {
        m_envelope.setValue<ADREnvelope::State::Decay>(value / 1000.0);
      },
      [](auto value) {
        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << value / 1000.0 << "%";
        return ss.str();
      }));
  DecayVal->initializeSlider((m_envelope.getLevel<ADREnvelope::State::Decay>() * 1000.0));

}
