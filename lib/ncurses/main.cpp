//
// Created by vincent.mesquita on 3/19/17.
//

#include <iostream>

#include "src/Window.h"
#include <ncurses/curses.h>
#include <dlfcn.h>


int main(void)
{
  void	*ptr;

  if (!(ptr = dlopen("libtest.so", RTLD_LOCAL | RTLD_LAZY)))
  {
    std::cerr << "dlopen failed" << std::endl;
    return (1);
  }
  arcade::Window w;

  // return (0);
  while (42)
    {
//    refresh();
      // printw("bonjour");
      w.refresh();
      w.event();
    }
  return (0);
}
