#pragma once
#include "../ModularPlaygroundApplication.h"
#include <Wt/WApplication.h>

class ModularWebUI : public Wt::WApplication {
public:
    ModularWebUI(const Wt::WEnvironment &env, ModularPlaygroundApplication &app, const char* basePath);
    void init();
protected:
    ModularPlaygroundApplication &m_application;
};
