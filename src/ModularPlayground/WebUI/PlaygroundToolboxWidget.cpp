#include "PlaygroundToolboxWidget.h"
#include "ModularWebUI.h"
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>

PlaygroundToolboxWidget::PlaygroundToolboxWidget(ModularPlaygroundApplication *application) : m_application{application} {
  auto combobox = addWidget(std::make_unique<Wt::WComboBox>());
  combobox->addItem("BangModule");
  combobox->addItem("DrumModule");
  combobox->addItem("MultiplyModule");

  auto createButton = addWidget(std::make_unique<Wt::WPushButton>());
  createButton->clicked().connect([this, combobox]() {
    ModularWebUI::createModuleFromString(m_application, combobox->currentText().toUTF8().data());
  });
}
