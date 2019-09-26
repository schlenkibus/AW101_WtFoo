#include "ModularPlaygroundApplication.h"
#include <dlfcn.h>

static void loadPlugins(ModularPlaygroundApplication* application) {

    void *hndl = dlopen("../FancyModule/libFancyModuleExample.so", RTLD_NOW);
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
    typedef void (*fptr)(DSPHost* h);
    fptr my_fptr = reinterpret_cast<fptr>(reinterpret_cast<long>(registerModulePtr)) ;
    my_fptr(application);
}