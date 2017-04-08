//
// Created by florian on 4/4/17.
//

#include <unistd.h>
#include <dlfcn.h>
#include "src/Window.hpp"
#include "src/Object.hpp"
#include "../../src/LibraryManager.hpp"
#include "IGraphicalLib.hpp"

typedef arcade::IGraphicalLib *(*fptr)(void*);

int         main(void)
{
  void	*ptr;
  fptr	lib_fptr;
  arcade::IGraphicalLib	*lib;
  std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> m(new std::vector<std::shared_ptr<arcade::IObject>>());

  if (!(ptr = dlopen("../lib_arcade_opengl.so", RTLD_NOW|RTLD_LAZY)))
    {
      fputs (dlerror(), stderr);
      return (1);
    }
  std::cout << "fdp\n";
  lib_fptr = (fptr)dlsym(ptr, "getNewLib");
  std::cout << "fdp1\n";
  arcade::IWindows *w;
  std::cout << "fdp2\n";
  try {
    lib = lib_fptr(ptr);
    std::cout << "fdp3\n";
    lib->initWindows(m);
    std::cout << "fdp4\n";
    w = lib->getWindows().get();
    std::cout << "fdp5\n";
    std::shared_ptr<arcade::IObject> obj2 = lib->initObject("Pacmann", "./resources/ghost");
    std::shared_ptr<arcade::IObject> obj3 = lib->initObject("Pacmann", "./resources/pacman");
    std::shared_ptr<arcade::IObject> obj = lib->initLabel("Pacman", "./resources/crackman");
    obj->setString("Hello World");
    // std::shared_ptr<arcade::IObject> obj3 = lib->initObject("Pacman", "./resources/pacman");
    // std::shared_ptr<arcade::IObject> obj4 = lib->initObject("Pacman", "./resources/pacmanx");
    // w->addObject(obj3);
    // w->addObject(obj2);
    w->addObject(obj);
  }
  catch (std::exception &e)
    {
      std::cout << "AError : " << e.what() << std::endl;
      exit(42);
    }
  w->refresh();
  sleep(3);
  std::cout << "end\n";
}
