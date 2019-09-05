#pragma once
#include "../Audio/Track.h"
#include "GenericButtonWidget.h"

namespace MixerDetail {
static std::unique_ptr<GenericButtonWidget>
createPlayButton(Track *t, const char *caption) {
  auto ptr = std::make_unique<GenericButtonWidget>(
      "Play Track 1", [t, caption](auto &widget) {
        if (!t->isPlaying())
          t->play();
        else
          t->pause();
        widget.setText(t->isPlaying() ? std::string("Pause ") + caption
                                      : std::string("Play ") + caption);
      });
  ptr->setEnabled(t->isTrackLoaded());
  return std::move(ptr);
};
} // namespace MixerDetail