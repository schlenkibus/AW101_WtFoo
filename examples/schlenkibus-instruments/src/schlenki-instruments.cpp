#include <libDSP/include/DSPHost.h>
#include <ModularWebUI.h>
#include "PlayerPlayer.h"
#include "PlayerPlayerWidget.h"

extern "C"
{
  void DSPPlugin_registerModule(DSPHost* h)
  {
    h->registerModule("player-player", [](DSPHost* h) { return new PlayerPlayer(h); });
  }

  void WEBUI_registerModule(ModularWebUI* ui)
  {
    ui->registerModule("player-player", [](DSPModule* player_player_module) -> std::unique_ptr<ModuleWidget> {
      return std::move(std::make_unique<PlayerPlayerWidget>(dynamic_cast<PlayerPlayer*>(player_player_module)));
    });
  }
}
