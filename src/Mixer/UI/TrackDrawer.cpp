#include "TrackDrawer.h"
#include <Wt/WPainter.h>

TrackDrawer::TrackDrawer(Track &track, Wt::WColor &color, int yOffset)
    : m_track{track}, m_color{color}, m_brush{m_color}, m_yOffset{yOffset}, m_backgroundColor{0, 0, 0}, m_background{m_backgroundColor} {
}

void TrackDrawer::paintTrack(Wt::WPainter &painter) {
  auto pos = std::max(1, m_track.getPlaybackPosition());
  auto percentage = pos / std::max<double>(1, m_track.getTrackLenghtInSamples());

  painter.setBrush(m_background);
  painter.drawRect(0, m_yOffset, 250, 50);

  painter.setBrush(m_brush);
  painter.drawRect(0, m_yOffset, percentage * 250, 50);
}


