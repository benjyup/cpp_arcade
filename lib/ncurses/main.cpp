//
// Created by vincent.mesquita on 3/19/17.
//

#include <iostream>

#include <ncurses/curses.h>
#include <dlfcn.h>
#include "IGraphicalLib.hpp"
#include "src/Window.hpp"
#include "src/Object.hpp"
#include "src/LibraryManager.hpp"

#include <stdlib.h>

typedef arcade::IGraphicalLib *(*fptr)(void*);

int main(void)
{

  /*arcade::LibraryManager lm;
  return (0);*/
  void	*ptr;
  fptr	lib_fptr;
  arcade::IGraphicalLib	*lib;
  std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> m(new std::vector<std::shared_ptr<arcade::IObject>>());

  if (!(ptr = dlopen("./lib_arcade_ncurses.so", RTLD_NOW|RTLD_LAZY)))
    {
      fputs (dlerror(), stderr);
      return (1);
    }
  lib_fptr = (fptr)dlsym(ptr, "getNewLib");
  arcade::IWindows *w;
  //std::shared_ptr<arcade::IWindows> w;
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
	  exit (42);
	}

      arcade::Vector3d pos1(10,10);
      obj2->setPosition(pos1);
      obj3->setPosition({20, 10});
      obj4->setPosition({30, 10});
      arcade::Vector3d pos(0,0);
  uint64_t x = 0;
  uint64_t y = 0;
      	while (w->event())
	{
//    refresh();
	  // printw("bonjour");
	  w->refresh();
	}
    } catch (std::exception &e) {
      endwin();
      std::cout << "Error : " << e.what() << std::endl;
    }
//  std::cout << w.use_count() << std::endl;
  delete lib;
  std::cout << "Timothée" << std::endl;
//  std::cout << w.use_count() << std::endl;
//  w.reset();
  m.reset();
  dlclose(ptr);
  std::cout << "Timothée" << std::endl;
  return (0);
}
