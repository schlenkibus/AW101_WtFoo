#include "PlaygroundToolboxWidget.h"
#include "ModularWebUI.h"
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>

PlaygroundToolboxWidget::PlaygroundToolboxWidget(ModularPlaygroundApplication *application) : m_application{application} {
  auto combobox = addWidget(std::make_unique<Wt::WComboBox>());
  combobox->addItem("BangModule");
  combobox->addItem("DrumModule");
  combobox->addItem("MultiplyModule");
  combobox->addItem("DuplicationModule");
  combobox->addItem("MixerModule");
  combobox->addItem("SineOscillatorModule");
  combobox->addItem("MagicNumberModule");

  auto createButton = addWidget(std::make_unique<Wt::WPushButton>());
  createButton->clicked().connect([this, combobox]() {
    ModularWebUI::createModuleFromString(m_application, combobox->currentText().toUTF8().data());
  });
  createButton->setText("Create selected module");
}
