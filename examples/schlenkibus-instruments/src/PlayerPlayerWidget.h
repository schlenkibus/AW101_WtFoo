#pragma once
#include <ModuleWidgets/ModuleWidget.h>
#include "PlayerPlayer.h"

class PlayerPlayerWidget : public ModuleWidget
{
 public:
  explicit PlayerPlayerWidget(PlayerPlayer* player);
  PlayerPlayer* getPlayerModule();
};