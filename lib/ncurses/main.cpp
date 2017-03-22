//
// Created by vincent.mesquita on 3/19/17.
//

#include <iostream>

#include "src/Window.h"
#include <ncurses/curses.h>

int main(void)
{
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
