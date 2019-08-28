#include <Wt/WApplication.h>
#include <Wt/WServer.h>
#include <utility>

#include "../SynthApplication.h"
#include "SampleInspectorWidget.h"

SampleInspectorWidget::SampleInspectorWidget(MySynthesizer& synth) : m_synth{synth} {
  backgroundColor.setRgb(250, 250, 250);
  fillbrush.setColor(backgroundColor);
  fillbrush.setStyle(Wt::BrushStyle::Solid);


  foregroundColor.setRgb(0, 0, 0);
  strokebrush.setColor(foregroundColor);
  strokebrush.setStyle(Wt::BrushStyle::Solid);

  resize(1200, 400);

  _running = true;

  update();

  m_backgroundThread = std::thread([this]() {
    while(_running) {
      Wt::WServer::instance()->postAll(&SynthApplication::signalUpdateInspector);
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  });

}



SampleInspectorWidget::~SampleInspectorWidget() {
  if(m_backgroundThread.joinable())
    m_backgroundThread.join();
}

void SampleInspectorWidget::paintEvent(Wt::WPaintDevice *paintDevice) {
  Wt::WPainter painter(paintDevice);
  painter.fillRect({0, 0, tWidth, 400}, fillbrush);



  auto& ringbuffer = m_synth.getRingBuffer();
  auto ptr = ringbuffer.getDataBeginPtr();

  float xInc = tWidth / ringbuffer.getSize();

  auto toY = [](float s) {
      return 200 + (s * 200);
  };

  auto width = std::max<int>(static_cast<int>(xInc), 1);

  double lastX = 0;
  int i = 0;
  while(i < ringbuffer.getSize()) {
    auto sample = *ptr;
    painter.fillRect(lastX, toY(sample), width, width, strokebrush);
    if(sample >= 1.0 || sample <= -1.0)
      std::cout << "sample out of bounds!" << std::endl;
    ptr++;
    lastX += xInc;
    i++;
  }

  _scheduled = false;
}

void SampleInspectorWidget::redraw() {
  update();
}
