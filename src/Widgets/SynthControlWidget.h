#pragma once

#include "../Synth/MySynthesizer.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>
#include <Wt/WSlider.h>

class SampleInspectorWidget;

class SynthControlWidget : public Wt::WContainerWidget {
public:
    SynthControlWidget(MySynthesizer& synthesizer);
    SampleInspectorWidget* getSampleInspector();
  protected:
    MySynthesizer& m_synth;
    SampleInspectorWidget* m_sampleInspector;
};
