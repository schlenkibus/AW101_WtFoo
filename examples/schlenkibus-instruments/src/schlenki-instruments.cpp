#include "schlenkibus-instruments.h"
#include <libDSP/include/DSPHost.h>
#include <ModularWebUI.h>
#include "PlayerPlayer.h"
#include "PlayerPlayerWidget.h"
#include "ButtonModule.h"
#include "ButtonModuleWidget.h"

extern "C"
{
  void DSPPlugin_registerModule(DSPHost* h)
  {
    h->registerModule("Sample Player", [](DSPHost* h) { return new PlayerPlayer(h); });
    h->registerModule("Button", [](DSPHost* h) { return new ButtonModule(h); });
  }
}

extern "C"
{
  void WEBUI_registerModule(ModularWebUI* ui)
  {
    ui->registerModule("Sample Player", [](DSPModule* player_player_module) -> std::unique_ptr<ModuleWidget> {
      return std::move(std::make_unique<PlayerPlayerWidget>(dynamic_cast<PlayerPlayer*>(player_player_module)));
    });

    ui->registerModule("Button", [](DSPModule* buttonMod) -> std::unique_ptr<ModuleWidget> {
      return std::move(std::make_unique<ButtonModuleWidget>(dynamic_cast<ButtonModule*>(buttonMod)));
    });
  }
}