#include "ModularPlaygroundApplication.h"
#include <libDSP/include/plugin/PluginLoader.h>
#include <dlfcn.h>
#include <libFilesystem/libFilesystem/include/Directory.h>
#include <libFilesystem/libFilesystem/include/FileTools.h>
#include <HAL/HAL/HAL.h>

template<typename tCallbackType>
tCallbackType loadLibraryAndGetFunctionPointer(const File &objectFile, const char *functionHandle) {
    void *hndl = dlopen(objectFile.getAbsoulutePath().data(), RTLD_NOW);

    if (hndl == nullptr) {
        std::cerr << dlerror() << std::endl;
        return nullptr;
    }

    void *registerModulePtr = dlsym(hndl, functionHandle);

    if (registerModulePtr == nullptr) {
        std::cerr << dlerror() << std::endl;
        return nullptr;
    }

    return reinterpret_cast<tCallbackType>(reinterpret_cast<long>(registerModulePtr));
}

static void loadDSPModules(ModularPlaygroundApplication *app, const Directory &dir) {
    if (app) {
        for (auto &objFile: FileTools::recurseDirectory(dir, [](const File &f) {
            return f.getPath().extension().string() == ".so";
        })) {
            typedef void (*tRegisterModule)(DSPHost *h);
            if (auto registerModule = loadLibraryAndGetFunctionPointer<tRegisterModule>(objFile,
                                                                                        "DSPPlugin_registerModule"))
                registerModule(app);
        }
    }
}

static void loadHardwareModules(HAL *hal, const Directory &hwDir) {
    if (hal) {
        for (auto &objectFile :
                FileTools::recurseDirectory(hwDir,
                                            [](const File &f) { return f.getPath().extension().string() == ".so"; })) {
            typedef void (*tRegisterHardware)(HAL *h);
            if (auto registerModule = loadLibraryAndGetFunctionPointer<tRegisterHardware>(objectFile,
                                                                                          "HAL_registerHardware"))
                registerModule(hal);
        }
    }
}

class UglyLoader : public PluginLoader {
 public:
  explicit UglyLoader(DSPHost* host) : PluginLoader(host) {
  }
  void loadPlugin(const File &sharedFile) override
  {
    typedef void (*tRegisterModule)(DSPHost *h);
    if (auto registerModule = loadLibraryAndGetFunctionPointer<tRegisterModule>(sharedFile,
                                                                                "DSPPlugin_registerModule"))
      registerModule(m_host);
  }
};