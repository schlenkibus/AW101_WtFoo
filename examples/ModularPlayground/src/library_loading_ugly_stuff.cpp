#include "ModularPlaygroundApplication.h"
#include <dlfcn.h>
#include <libFilesystem/libFilesystem/include/Directory.h>
#include <libFilesystem/libFilesystem/include/FileTools.h>
#include <HAL/HAL/HAL.h>

template <typename tCallbackType>
tCallbackType loadLibraryAndGetFunctionPointer(const File& objectFile, const char* functionHandle)
{
  void* hndl = dlopen(objectFile.getAbsoulutePath().data(), RTLD_NOW);

  if(hndl == nullptr)
  {
    std::cerr << dlerror() << std::endl;
    return nullptr;
  }

  void* registerModulePtr = dlsym(hndl, functionHandle);

  if(registerModulePtr == nullptr)
  {
    std::cerr << dlerror() << std::endl;
    return nullptr;
  }

  return reinterpret_cast<tCallbackType>(reinterpret_cast<long>(registerModulePtr));
}

static void loadPlugins(ModularPlaygroundApplication* application, HAL* hal, const Directory& dspDir,
                        const Directory& hwDir)
{
  if(application)
  {
    for(auto& objectFile :
            FileTools::recurseDirectory(dspDir, [](const File& f) { return f.getPath().extension().string() == ".so"; }))
    {

      typedef void (*tRegisterModule)(DSPHost * h);
      if(auto registerModule = loadLibraryAndGetFunctionPointer<tRegisterModule>(objectFile, "DSPPlugin_registerModule"))
        registerModule(application);
    }
  }

  if(hal)
  {
    for(auto& objectFile :
            FileTools::recurseDirectory(hwDir, [](const File& f) { return f.getPath().extension().string() == ".so"; }))
    {
      typedef void (*tRegisterHardware)(HAL * h);
      if(auto registerModule = loadLibraryAndGetFunctionPointer<tRegisterHardware>(objectFile, "HAL_registerHardware"))
        registerModule(hal);
    }
  }
}