//
// Created by vincent.mesquita on 3/19/17.
//

#include <iostream>

#include "src/Window.h"

int main(void)
{
    arcade::Window w;

    while (42)
    {
        w.refresh();
        w.event();
    }
    return (0);
}
