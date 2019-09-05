#include "MixerWidget.h"
#include "../../Widgets/ParameterPack.h"
#include "GenericButtonWidget.h"
#include "SamplePreviewWidget.h"
#include "Wt/WFileUpload.h"
#include "Wt/WComboBox.h"

MixerWidget::MixerWidget(DSPHost &mixer) : m_mixer{mixer} {

  auto play1 = addWidget(std::make_unique<GenericButtonWidget>(
      "Play Track 1", [this](auto &widget) {
        if (!m_mixer.m_track1.isPlaying())
          m_mixer.m_track1.play();
        else
          m_mixer.m_track1.pause();

        widget.setText(m_mixer.m_track1.isPlaying() ? "Pause Track 1"
                                                    : "Play Track 1");
      }));

  play1->setEnabled(false);

  auto play2 = addWidget(std::make_unique<GenericButtonWidget>(
      "Play Track 2", [this](auto &widget) {
        if (!m_mixer.m_track2.isPlaying())
          m_mixer.m_track2.play();
        else
          m_mixer.m_track2.pause();

        widget.setText(m_mixer.m_track2.isPlaying() ? "Pause Track 2"
                                                    : "Play Track 2");
      }));

  play2->setEnabled(false);

  auto soundList = addWidget(std::make_unique<Wt::WComboBox>());
  for(auto& file: std::experimental::filesystem::recursive_directory_iterator(".")) {
    if(file.symlink_status().type() != std::experimental::filesystem::file_type::directory) {
      if(file.path().extension().string() == ".wav") {
        try {
          mixer.loadSound(file.path());
          soundList->addItem(file.path().string());
        } catch(...) {
          soundList->addItem("Corrupted: " + file.path().root_name().string());
        }
      }
    }
  };

  auto loadIntoTrack1 = addWidget(std::make_unique<GenericButtonWidget>("Load selected Song into track 1", [this, soundList, play1](auto& widget) {
    auto selected = soundList->currentText();
    try {
      m_mixer.m_track1.setSoundFile(m_mixer.m_sounds.getSound(selected.toUTF8()));
      play1->setEnabled(true);
    } catch(...) {}
  }));



  auto loadIntoTrack2 = addWidget(std::make_unique<GenericButtonWidget>("Load selected Song into track 2", [this, soundList, play2](auto& widget) {
    auto selected = soundList->currentText();
    try {
      m_mixer.m_track2.setSoundFile(m_mixer.m_sounds.getSound(selected.toUTF8()));
      play2->setEnabled(true);
    } catch(...) {}
  }));


  addWidget(std::make_unique<ParameterPack>(
      "Crossfade 1 <-> 2", -100, 100,
      [this](auto value) { m_mixer.setCrossFade(value / 100.0); },
      [](auto value) {
        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << value / 100.0;
        return ss.str();
      }));

  addWidget(std::make_unique<ParameterPack>(
      "Seek 1", -1000, 1000,
      [this](auto value) { m_mixer.m_track1.setPlaybackSpeed(value / 100.0); },
      [](auto value) {
        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << value / 100.0 << "x";
        return ss.str();
      }));

  addWidget(std::make_unique<ParameterPack>(
      "Seek 2", -1000, 1000,
      [this](auto value) { m_mixer.m_track2.setPlaybackSpeed(value / 100.0); },
      [](auto value) {
        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << value / 100.0 << "x";
        return ss.str();
      }));

  m_previewWidget = addWidget(std::make_unique<SamplePreviewWidget>(m_mixer));
}

void MixerWidget::redraw() {
    m_previewWidget->update(Wt::PaintFlag::Update);
}
