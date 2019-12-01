#pragma once

#include <libDSP/include/plugin/PluginLoader.h>
#include <dlfcn.h>

/* WEBUI_registerModule */

class WebUIPluginLoader : public PluginLoader
{
 private:
  template <typename tCallbackType>
  inline tCallbackType loadLibraryAndGetFunctionPointer(const File &objectFile, const char *functionHandle)
  {
    void *hndl = dlopen(objectFile.getAbsoulutePath().data(), RTLD_NOW);

    if(hndl == nullptr)
    {
      std::cerr << dlerror() << std::endl;
      return nullptr;
    }

    void *registerModulePtr = dlsym(hndl, functionHandle);

    if(registerModulePtr == nullptr)
    {
      std::cerr << dlerror() << std::endl;
      return nullptr;
    }

    return reinterpret_cast<tCallbackType>(reinterpret_cast<long>(registerModulePtr));
  }

 public:
  explicit WebUIPluginLoader(ModularWebUI *ui)
      : PluginLoader { nullptr }
      , m_ui { ui }
  {
  }

  void loadPlugin(const File &sharedFile) override
  {
    typedef void (*tRegisterModule)(ModularWebUI * m);
    if(auto registerModule = loadLibraryAndGetFunctionPointer<tRegisterModule>(sharedFile, "WEBUI_registerModule"))
      registerModule(m_ui);
  }

 private:
  ModularWebUI *m_ui;
};
