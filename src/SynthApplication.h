#pragma once

#include "Synth/MySynthesizer.h"
#include "Widgets/SynthControlWidget.h"
#include <Wt/WApplication.h>

class SynthApplication : public Wt::WApplication
{
public:
    SynthApplication(const Wt::WEnvironment& env, MySynthesizer& synthesizer);

    static void signalUpdateInspector();
private:
    MySynthesizer& m_synthesizer;
    SynthControlWidget* m_widget;
};