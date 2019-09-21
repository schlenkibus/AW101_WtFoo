#include "DrumModuleWidget.h"
#include "../../../Mixer/UI/ParameterPack.h"
#include "../../Modules/DrumModule.h"

DrumModuleWidget::DrumModuleWidget(DrumModule *module) : ModuleWidget(module) {
  addWidget(std::make_unique<ParameterPack>("Start Frequency", 3000, 12000, [module](auto value) {
      module->setBaseFrequency(value / 10.0);
    }, [](auto value) -> std::string {
    return std::to_string(value / 10.0) + " Hz";
  }));
}
