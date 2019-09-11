#include "EnvelopeWidget.h"
#include "../../Synth/DSPInfo.h"
#include "../../Widgets/ParameterPack.h"

EnvelopeWidget::EnvelopeWidget(ADREnvelope &envelope,
                               const std::string &baseName)
    : m_envelope{envelope} {
  auto pitchAttack = addWidget(std::make_unique<ParameterPack>(
      baseName + " Envelope Attack Time", 10, 2000,
      [this](auto value) {
        m_envelope.setLength<ADREnvelope::State::Attack>(DSPInfo::SampleRate *
                                                         (value / 1000.0));
      },
      [](auto value) {
        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << value / 1000.0 << " S";
        return ss.str();
      }));

  auto pitchDecay = addWidget(std::make_unique<ParameterPack>(
      baseName + " Envelope Decay Time", 10, 2000,
      [this](auto value) {
        m_envelope.setLength<ADREnvelope::State::Decay>(DSPInfo::SampleRate *
                                                        (value / 1000.0));
      },
      [](auto value) {
        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << value / 1000.0 << " S";
        return ss.str();
      }));

  auto pitchRelease = addWidget(std::make_unique<ParameterPack>(
      baseName + " Envelope Release Time", 10, 5000, [this](auto value) {
        m_envelope.setLength<ADREnvelope::State::Release>(DSPInfo::SampleRate *
                                                          (value / 1000.0));
      },
      [](auto value) {
        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << value / 1000.0 << " S";
        return ss.str();
      }));

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
}
