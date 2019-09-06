#include "TrackDrawer.h"
#include <Wt/WPainter.h>

TrackDrawer::TrackDrawer(Track &track, Wt::WColor &color, int yOffset)
    : m_track{track}, m_color{color}, m_playbackBarBrush{m_color},
      m_yOffset{yOffset}, m_backgroundColor{0, 0, 0},
      m_background{m_backgroundColor}, m_loopOverlayColor{0, 255, 0, 127},
      m_loopOverlayBrush{m_loopOverlayColor} {}

void TrackDrawer::paintTrack(Wt::WPainter &painter) {
  auto pos = std::max(1, m_track.getPlaybackPosition());
  auto percentage =
      pos / std::max<double>(1, m_track.getTrackLenghtInSamples());

  auto loopStart = m_track.getLoopStartPercent();
  auto loopEnd = m_track.getLoopEndPercent();


  painter.setBrush(m_background);
  painter.drawRect(0, m_yOffset, 250, 50);

  painter.setBrush(m_loopOverlayBrush);
  painter.drawRect(loopStart * 250, m_yOffset, (loopEnd - loopStart) * 250, 50);

  painter.setBrush(m_playbackBarBrush);
  painter.drawRect(loopStart * 250, 10, (percentage* 250) - loopStart * 250, 30);


}
