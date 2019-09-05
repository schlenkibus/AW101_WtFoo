#include <utility>

#include "DSPHostUserInterfaceApplication.h"
#include "MixerDetail.h"
#include "TrackWidget.h"

TrackWidget::TrackWidget(std::string caption, Track &track)
    : m_track{track}, m_caption{std::move(caption)} {


  m_explorer = addWidget(std::make_unique<FileExplorerWidget>(
      DSPHostUserInterfaceApplication::sBasePath, [this](const File *file) {
        m_track.setSoundFile(
            SoundStorage::get().getSound(file->getAbsoulutePath().data()));
        m_playbutton->setEnabled(true);
      }));

  m_explorer->addStyleClass("explorer-widget");

  auto controlsContainer = addWidget(std::make_unique<Wt::WContainerWidget>());
  controlsContainer->addStyleClass("play-controls-container");

  m_playbutton =
      controlsContainer->addWidget(MixerDetail::createPlayButton(&m_track, m_caption.data()));

  auto converter = [](auto value) {
    std::stringstream ss;
    ss.precision(2);
    ss << std::fixed << value / 100.0;
    return ss.str();
  };

  auto speed = controlsContainer->addWidget(std::make_unique<ParameterPack>(
      std::string("Speed") + caption, -1000, 1000,
      [this](auto value) { m_track.setPlaybackSpeed(value / 100.0); },
      converter));

  speed->initializeSlider(static_cast<int>(m_track.getPlaybackSpeed() * 100));

  m_preview = controlsContainer->addWidget(std::make_unique<SamplePreviewWidget>(m_track));

  addStyleClass("trackwidget-container");
}

SamplePreviewWidget *TrackWidget::getPreview() { return m_preview; }
