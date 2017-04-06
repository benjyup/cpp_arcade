//
// Created by florian on 4/4/17.
//

#include <dlfcn.h>
#include "IGraphicalLib.hpp"

typedef arcade::IGraphicalLib *(*fptr)(void*);

int         main(void)
{
    void	*ptr;
    fptr	lib_fptr;
    arcade::IGraphicalLib	*lib;
    std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> m(new std::vector<std::shared_ptr<arcade::IObject>>());

    if (!(ptr = dlopen("./lib_arcade_opengl.so", RTLD_NOW|RTLD_LAZY)))
    {
        fputs (dlerror(), stderr);
        return (1);
    }
    lib_fptr = (fptr)dlsym(ptr, "getNewLib");
    arcade::IWindows *w;
    try {
        lib = lib_fptr(ptr);
        lib->initWindows(m);
        w = lib->getWindows().get();
        std::shared_ptr<arcade::IObject> obj2 = lib->initObject("Pacmann", "./resources/xelow");
        std::shared_ptr<arcade::IObject> obj = lib->initObject("Pacman", "./resources/pacman");
        std::shared_ptr<arcade::IObject> obj3 = lib->initObject("Pacman", "./resources/pacman");
        std::shared_ptr<arcade::IObject> obj4 = lib->initObject("Pacman", "./resources/pacmanx");
        try {
            w->addObject(obj);
        } catch (std::exception &e) {
            endwin();
            std::cout << "AError : " << e.what() << std::endl;
            exit(42);
        }
}