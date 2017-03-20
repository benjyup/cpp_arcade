//
// Created by vincent.mesquita on 3/19/17.
//

#include <iostream>

#include "src/Window.h"
#include <ncurses/curses.h>

int main(void)
{
    arcade::Window w;

    while (42)
    {
      // printw("bonjour");
      move(0, 0);
      // w.refresh();
      w.event();
      refresh();
    }
    return (0);
}
