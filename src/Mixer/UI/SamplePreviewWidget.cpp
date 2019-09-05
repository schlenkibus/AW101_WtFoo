#include "SamplePreviewWidget.h"
#include "../../Synth/DSPInfo.h"
#include "DSPHostUserInterfaceApplication.h"
#include <Wt/WPaintDevice.h>
#include <Wt/WPainter.h>
#include <Wt/WServer.h>
#include <Wt/WColor.h>
#include <Wt/WTimer.h>

SamplePreviewWidget::SamplePreviewWidget(Track &track)
    : m_track{track}
    , m_trackDraw{m_track, blue, 0}
{
  resize(250, 50);
  update();
  auto timer = addChild(std::make_unique<Wt::WTimer>());
  timer->setInterval(std::chrono::milliseconds(20));
  timer->setSingleShot(false);
  timer->timeout().connect([this]{
      update();
  });
  timer->start();
}

void SamplePreviewWidget::paintEvent(Wt::WPaintDevice *paintDevice) {
  Wt::WPainter painter(paintDevice);
  m_trackDraw.paintTrack(painter);
}
