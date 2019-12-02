#pragma once

class DSPHost;
class ModularWebUI;

extern "C" void DSPPlugin_registerModule(DSPHost* h);
extern "C" void WEBUI_registerModule(ModularWebUI* h);