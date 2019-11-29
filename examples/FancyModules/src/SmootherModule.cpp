#include "SmootherModule.h"

inline float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

void SmootherModule::tick() {
    DSPContainer::tick();

    m_output->set(lerp(m_input->getSignal(), m_lastSignal, m_smoothingFactor->getValue()));
}

SmootherModule::SmootherModule(DSPHost *parent) : DSPModule(parent) {
    m_smoothingFactor = createParameter("Smoothing", 0.5, 0.0, 1.0);
    m_input = createInput("Input");
    m_output = createOutput("Smoothed");
}
