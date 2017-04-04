//
// Created by vincent on 04/04/17.
//

#include <dlfcn.h>
#include "IGraphicalLib.hpp"
#include "IGameLib.hpp"

typedef arcade::IGameLib *(*fptr)(void*);

int     main(void)
{
    void *handle = dlopen("../lib_arcade_snake.so", RTLD_NOW | RTLD_LAZY);
    if (!handle)
    {
        fputs (dlerror(), stderr);
        return (1);
    }
    fptr lib_fptr = (fptr)dlsym(handle, "getNewLib");
    if (!lib_fptr)
    {
        fputs (dlerror(), stderr);
        return (1);
    }

    arcade::IGameLib *gameLib;
    std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> obj;

    try {
        gameLib = lib_fptr(handle);
        gameLib->initGame(NULL, obj);
    } catch (const std::exception &e) {
        std::cout << "Error: " + std::string(e.what()) << std::endl;
    }
    dlclose(handle);
//    delete gameLib;
    return (0);
}