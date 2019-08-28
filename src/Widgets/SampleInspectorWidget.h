#pragma once
#include "../Synth/MySynthesizer.h"
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainter.h>
#include <atomic>
#include <condition_variable>
#include <thread>

class SampleInspectorWidget : public Wt::WPaintedWidget {
public:
  explicit SampleInspectorWidget(MySynthesizer& synth);
  ~SampleInspectorWidget() override;
  void redraw();
protected:
  void paintEvent(Wt::WPaintDevice *paintDevice) override;

  MySynthesizer& m_synth;
  std::atomic_bool _running = {false};
  std::atomic_bool _scheduled = {false};

  Wt::WBrush fillbrush;
  Wt::WColor foregroundColor;
  Wt::WBrush strokebrush;
  Wt::WColor backgroundColor;

  std::thread m_backgroundThread;

  static constexpr const float tWidth = 1000.0;
};
