#pragma once
#include "ModularPlaygroundApplication.h"
#include <libDSP/include/plugin/PluginLoader.h>
#include <dlfcn.h>
#include <libFilesystem/libFilesystem/include/Directory.h>
#include <libFilesystem/libFilesystem/include/FileTools.h>
#include <HAL/HAL/HAL.h>

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

class UglyLoader : public PluginLoader
{
 public:
  explicit UglyLoader(DSPHost *host)
      : PluginLoader(host)
  {
  }
  void loadPlugin(const File &sharedFile) override
  {
    if(auto registerModule = loadLibraryAndGetFunctionPointer<tRegisterModule>(sharedFile, "DSPPlugin_registerModule"))
      registerModule(m_host);
  }
};