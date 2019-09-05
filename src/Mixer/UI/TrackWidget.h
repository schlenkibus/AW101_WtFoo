#pragma once
#include "../../Widgets/ParameterPack.h"
#include "../Audio/Track.h"
#include "FileExplorerWidget.h"
#include "GenericButtonWidget.h"
#include "SamplePreviewWidget.h"
#include <Wt/WContainerWidget.h>

class TrackWidget : public Wt::WContainerWidget {
public:
    TrackWidget(std::string  caption, Track& track);
  SamplePreviewWidget* getPreview();
  protected:
    std::string m_caption;
    Track& m_track;

    FileExplorerWidget* m_explorer = nullptr;
    SamplePreviewWidget* m_preview = nullptr;
    GenericButtonWidget* m_playbutton = nullptr;
    ParameterPack* m_playbackFactor = nullptr;
};
