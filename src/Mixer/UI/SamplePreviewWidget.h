#pragma once

#include "../Audio/DSPHost.h"
#include "TrackDrawer.h"
#include <Wt/WBrush.h>
#include <Wt/WColor.h>
#include <Wt/WPaintedWidget.h>
#include <thread>
class SamplePreviewWidget : public Wt::WPaintedWidget {
public:
  explicit SamplePreviewWidget(DSPHost &mixer);

protected:
  void paintEvent(Wt::WPaintDevice *paintDevice) override;

  DSPHost &m_mixer;
  Wt::WColor red{255, 0, 0, 127};
  Wt::WColor blue{0, 0, 255, 127};

  TrackDrawer m_trackDraw1;
  TrackDrawer m_trackDraw2;
};
