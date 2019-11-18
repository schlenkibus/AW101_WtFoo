#pragma once
#include "WaveTableOscillator.h"
#include <libDSP/include/Modules/DSPModule.h>

template <typename WaveTableOscillator>
class OscillatorModule : public DSPModule {
public:
  explicit OscillatorModule(DSPHost *host, const char *name)
      : DSPModule(host), m_osc{host}, m_name{name} {
    m_signalOut = createOutput("Sine");
    createInput("Frequency");
    createInput("Reset");

    createParameter("Base Frequency", 440, 1, 3520, 0);
    createParameter("Fine Tune", 0, -1, 1, 3);
    createParameter("Frequency Range", 0, -0.99, 0.99, 2);

    m_frequencyRange = findParameter("Frequency Range");
    m_baseFrequency = findParameter("Base Frequency");
    m_fineTune = findParameter("Fine Tune");

    m_resetIn = findInput("Reset");
    m_frequencyIn = findInput("Frequency");
  }

  void tick() override {
    DSPContainer::tick();

    if (m_resetIn->getSignal() != 0.0f) {
      m_osc.reset();
      m_signalOut->set(0);
      return;
    }

    const auto fullFrequency = m_baseFrequency->getValue() + m_fineTune->getValue();

    m_osc.setFrequency(
        fullFrequency +
        (m_frequencyIn->getSignal() * (fullFrequency * m_frequencyRange->getValue())));

    m_osc.tick();
    m_signalOut->set(m_osc.signal);
  }

  const char *getName() override {
    return m_name.data();
  };

private:
  std::string m_name;
  WaveTableOscillator m_osc;
  Output *m_signalOut;
  Input *m_frequencyIn;
  Input *m_resetIn;

  Parameter *m_baseFrequency;
  Parameter *m_fineTune;
  Parameter *m_frequencyRange;
};