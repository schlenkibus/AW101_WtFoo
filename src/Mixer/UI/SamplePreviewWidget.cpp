#include "SamplePreviewWidget.h"
#include "../../Synth/DSPInfo.h"
#include "DSPHostUserInterfaceApplication.h"
#include <Wt/WPaintDevice.h>
#include <Wt/WPainter.h>
#include <Wt/WServer.h>
#include <Wt/WColor.h>

SamplePreviewWidget::SamplePreviewWidget(DSPHost &mixer)
    : m_mixer{mixer}
    , m_trackDraw1{m_mixer.m_track1, red, 0}
    , m_trackDraw2{m_mixer.m_track2, blue, 150}
{
  resize(1000, 300);
  update();
}

void SamplePreviewWidget::paintEvent(Wt::WPaintDevice *paintDevice) {
  Wt::WPainter painter(paintDevice);
  m_trackDraw1.paintTrack(painter);
  m_trackDraw2.paintTrack(painter);
}
