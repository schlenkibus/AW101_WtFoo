#pragma once

#include "../Audio/DSPHost.h"
#include "TrackDrawer.h"
#include <Wt/WBrush.h>
#include <Wt/WColor.h>
#include <Wt/WPaintedWidget.h>
#include <thread>
class SamplePreviewWidget : public Wt::WPaintedWidget {
public:
  explicit SamplePreviewWidget(Track &track);

protected:
  void paintEvent(Wt::WPaintDevice *paintDevice) override;

  Track &m_track;
  Wt::WColor blue{0, 0, 255};

  TrackDrawer m_trackDraw;
};
