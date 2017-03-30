//
// Created by vincent.mesquita on 3/19/17.
//

#include <iostream>

#include <ncurses/curses.h>
#include <dlfcn.h>
#include <iostream>
#include "IGraphicalLib.hpp"
#include "IWindows.hpp"
#include "Window.hpp"
#include "IObject.hpp"
#include "src/Window.hpp"
#include "src/Object.hpp"
#include <vector>

#include <stdlib.h>

typedef arcade::IGraphicalLib *(*fptr)(void*);

int main(void)
{
  void	*ptr;
  fptr	lib_fptr;
  arcade::IGraphicalLib	*lib;
  std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> m(new std::vector<std::shared_ptr<arcade::IObject>>());

  if (!(ptr = dlopen("./lib_arcade_ncurses.so", RTLD_NOW|RTLD_LAZY)))
    {
      fputs (dlerror(), stderr);
      exit(1);
      return (1);
    }
  lib_fptr = (fptr)dlsym(ptr, "getNewLib");
  std::shared_ptr<arcade::IWindows> w;
  try {
      lib = lib_fptr(ptr);
      lib->initWindows(m);
      w = lib->getWindows();
      std::shared_ptr<arcade::IObject> obj = lib->initObject("Pacman", "resources/pacman.ncurses");
      try {
	  w->addObject(obj);
	} catch (std::exception &e) {
	  endwin();
	  std::cout << "AError : " << e.what() << std::endl;
	  exit (42);
	}

  	arcade::Vector3d pos(0,0);
  uint64_t x = 0;
  uint64_t y = 0;
      	while (42)
	{
//    refresh();
	  // printw("bonjour");
	  obj->setPosition(pos);
	  w->refresh();
	  w->event();
	    pos.setX(x);
	    pos.setY(y);
	    x = (x + 1) % 50;
	}
    } catch (std::exception &e) {
      endwin();
      std::cout << "Error : " << e.what() << std::endl;
    }
  std::cout << w.use_count() << std::endl;
  delete lib;
  std::cout << "Timothée" << std::endl;
  std::cout << w.use_count() << std::endl;
  w.reset();
  m.reset();
  dlclose(ptr);
  std::cout << "Timothée" << std::endl;
  return (0);
}
