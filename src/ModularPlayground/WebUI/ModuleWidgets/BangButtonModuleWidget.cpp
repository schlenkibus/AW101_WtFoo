#include "BangButtonModuleWidget.h"
#include "../../Modules/BangModule.h"
#include <Wt/WPushButton.h>
#include <Wt/WSlider.h>
#include <Wt/WLabel.h>


BangButtonModuleWidget::BangButtonModuleWidget(BangModule *module) : ModuleWidget(module){
    auto button = addWidget(std::make_unique<Wt::WPushButton>());
    button->setText("Bang!");
    button->clicked().connect([this, module]() {
        module->sendBang();
    });

    auto length = addWidget(std::make_unique<Wt::WSlider>());
    length->setNativeControl(true);
    length->setRange(1, 100);


    auto label = addWidget(std::make_unique<Wt::WLabel>());

    length->changed().connect([module, label, length]() {
        auto value = length->value();
        auto inSeconds = value / 100.0;
        module->setBangLength(inSeconds);
        label->setText(std::to_string(inSeconds) + "sec");
    });

    label->setText(std::to_string(module->getBangLength()) + "sec");
}
