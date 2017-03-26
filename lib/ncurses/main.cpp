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
#include "src/Window.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

typedef arcade::IGraphicalLib *(*fptr)(void);

int main(void)
{
  void	*ptr;
  fptr	lib_fptr;
  arcade::IGraphicalLib	*lib;

  if (!(ptr = dlopen("./libtest.so", RTLD_NOW|RTLD_LAZY)))
    {
      fputs (dlerror(), stderr);
      exit(1);
      return (1);
    }
  lib_fptr = (fptr)dlsym(ptr, "getNewLib");
  lib = lib_fptr();

  std::shared_ptr<arcade::IWindows> w;
  w = lib->initWindows(50, 50);
  //arcade::IWindows *w = new arcade::Window(50, 50);

  // return (0);
  while (42)
    {
//    refresh();
      // printw("bonjour");
      w->refresh();
      w->event();
    }
  return (0);
}
