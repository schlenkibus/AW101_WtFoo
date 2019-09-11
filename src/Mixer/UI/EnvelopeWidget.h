#pragma once

#include "../../Synth/DSPNodes/ADREnvelope.h"
#include <Wt/WContainerWidget.h>
class EnvelopeWidget : public Wt::WContainerWidget {
public:
    explicit EnvelopeWidget(ADREnvelope& envelope, const std::string& baseName);
protected:
    ADREnvelope& m_envelope;
};
