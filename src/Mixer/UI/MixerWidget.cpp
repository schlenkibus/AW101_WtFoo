#include "MixerWidget.h"
#include "../../Widgets/ParameterPack.h"
#include "DSPHostUserInterfaceApplication.h"
#include "FileExplorerWidget.h"
#include "GenericButtonWidget.h"
#include "SamplePreviewWidget.h"
#include "Wt/WComboBox.h"
#include "Wt/WFileUpload.h"

#include "MixerDetail.h"
#include "TrackWidget.h"

MixerWidget::MixerWidget(DSPHost &mixer) : m_mixer{mixer} {

  m_track1 = addWidget(std::make_unique<TrackWidget>("I", m_mixer.m_track1));

  auto crossFade = addWidget(std::make_unique<ParameterPack>(
      "Crossfade 1 <-> 2", -100, 100,
      [this](auto value) { m_mixer.setCrossFade(value / 100.0); },
      [](auto value) {
        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << value / 100.0;
        return ss.str();
      }));
  crossFade->initializeSlider(static_cast<int>(m_mixer.getCrossFade() * 100));

  m_track2 = addWidget(std::make_unique<TrackWidget>("II", m_mixer.m_track2));

}

void MixerWidget::redraw() {
  if(m_track1->getPreview())
    m_track1->getPreview()->update(Wt::PaintFlag::Update);

  if(m_track2->getPreview())
    m_track2->getPreview()->update(Wt::PaintFlag::Update);
}
