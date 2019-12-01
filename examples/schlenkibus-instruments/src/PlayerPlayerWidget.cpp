#include <GenericWidgets/FileExplorerWidget.h>
#include "PlayerPlayerWidget.h"

PlayerPlayerWidget::PlayerPlayerWidget(PlayerPlayer* player)
    : ModuleWidget(player)
{
  addWidget(std::make_unique<FileExplorerWidget>(Directory("/home/justus/Music"),
                                                 [this](const auto* file) { getPlayerModule()->loadTrack(file); }));
}

PlayerPlayer* PlayerPlayerWidget::getPlayerModule()
{
  return dynamic_cast<PlayerPlayer*>(getModule());
}
