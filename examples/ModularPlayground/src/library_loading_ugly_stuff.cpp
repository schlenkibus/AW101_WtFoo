#include "ModularPlaygroundApplication.h"
#include <dlfcn.h>

static void loadPlugins(ModularPlaygroundApplication* application) {

    void *hndl = dlopen("../FancyModules/libFancyModuleExample.so", RTLD_NOW);
    if(hndl == nullptr){
        std::cerr << dlerror() << std::endl;
        exit(-1);
    }
    void* registerModulePtr = dlsym(hndl, "DSPPlugin_registerModule");

    if(registerModulePtr == nullptr){
      std::cerr << dlerror() << std::endl;
      exit(-1);
    }

#warning "Undefined Behaviour Land!!"

    typedef void (*tRegisterModule)(DSPHost* h);
    auto registerModule = reinterpret_cast<tRegisterModule>(reinterpret_cast<long>(registerModulePtr)) ;
    registerModule(application);
}