#pragma once
#include "../Audio/DSPHost.h"
#include "FileExplorerWidget.h"
#include "GenericButtonWidget.h"
#include <Wt/WContainerWidget.h>

class SamplePreviewWidget;
class TrackWidget;

class MixerWidget : public Wt::WContainerWidget {
public:
  MixerWidget(DSPHost &mixer);
  void redraw();

protected:
  SamplePreviewWidget *m_previewWidget;
  DSPHost &m_mixer;

  TrackWidget* m_track1, *m_track2;
};
