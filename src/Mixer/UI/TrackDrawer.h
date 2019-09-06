#pragma once

#include "../Audio/Track.h"
#include <Wt/WBrush.h>
#include <Wt/WColor.h>
#include <Wt/WPainterPath.h>

class TrackDrawer {
public:
    TrackDrawer(Track &track, Wt::WColor &color, int yOffset);
    void paintTrack(Wt::WPainter& painter);

protected:
    int m_yOffset;
    Track& m_track;


    Wt::WColor m_color;
    Wt::WColor m_loopOverlayColor;
    Wt::WColor m_backgroundColor;
    Wt::WBrush m_playbackBarBrush;
    Wt::WBrush m_loopOverlayBrush;
    Wt::WBrush m_background;
};