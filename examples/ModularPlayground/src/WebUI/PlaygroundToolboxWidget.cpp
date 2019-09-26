#include "PlaygroundToolboxWidget.h"
#include "ModularWebUI.h"
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>

PlaygroundToolboxWidget::PlaygroundToolboxWidget(ModularPlaygroundApplication *application) : m_application{application} {
  auto combobox = addWidget(std::make_unique<Wt::WComboBox>());
  for(auto& avail: m_application->getAvailableModules()) {
    combobox->addItem(avail);
  }

  auto createButton = addWidget(std::make_unique<Wt::WPushButton>());
  createButton->clicked().connect([this, combobox]() {
    auto name = combobox->currentText();
    auto str = name.toUTF8();
    m_application->pushCreation(str);
  });

  createButton->setText("Create selected module");
}
