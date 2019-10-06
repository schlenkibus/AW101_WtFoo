#include "ModularPlaygroundApplication.h"
#include <dlfcn.h>
#include <libFilesystem/libFilesystem/include/Directory.h>
#include <libFilesystem/libFilesystem/include/FileTools.h>

static void loadPlugins(ModularPlaygroundApplication *application,
                        const Directory &directory) {

    for(auto & objectFile: FileTools::recurseDirectory(directory, [](const File& f) {
        return f.getPath().extension().string() == ".so";
    })) {

        void *hndl = dlopen(objectFile.getAbsoulutePath().data(), RTLD_NOW);

        if(hndl == nullptr){
            std::cerr << dlerror() << std::endl;
            continue;
        }

        void* registerModulePtr = dlsym(hndl, "DSPPlugin_registerModule");

        if(registerModulePtr == nullptr){
            std::cerr << dlerror() << std::endl;
            continue;
        }

        #warning "Undefined Behaviour Land!!"
        typedef void (*tRegisterModule)(DSPHost* h);
        auto registerModule = reinterpret_cast<tRegisterModule>(reinterpret_cast<long>(registerModulePtr)) ;
        registerModule(application);
    }
}