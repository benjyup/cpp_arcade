//
// Created by vincent.mesquita on 3/19/17.
//

#include <iostream>

#include <ncurses/curses.h>
#include <dlfcn.h>
#include <iostream>
#include "IGraphicalLib.hpp"
#include "IWindows.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main(void)
{
  void	*ptr;
  //arcade::IGraphicalLib	*lib;

  if (!(ptr = dlopen("./libtest.so", RTLD_NOW|RTLD_LAZY)))
    {
      fputs (dlerror(), stderr);
      exit(1);
      return (1);
    }
/*  arcade::Window w;

  // return (0);
  while (42)
    {
//    refresh();
      // printw("bonjour");
      w.refresh();
      w.event();
    }*/
  return (0);
}
