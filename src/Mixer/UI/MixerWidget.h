#pragma once
#include "../Audio/DSPHost.h"
#include <Wt/WContainerWidget.h>

class SamplePreviewWidget;

class MixerWidget : public Wt::WContainerWidget {
public:
    MixerWidget(DSPHost& mixer);
    void redraw();
protected:
    SamplePreviewWidget* m_previewWidget;
    DSPHost& m_mixer;
};
