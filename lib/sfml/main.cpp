//
// main.cpp for Project-Master in /home/peixot_b/Epitech/Tek2/CPP/Arcade/cpp_arcade/lib/sfml
// 
// Made by peixot_b
// Login   <benjamin.peixoto@epitech.eu>
// 
// Started on  Wed Mar 22 17:19:21 2017 peixot_b
// Last update Wed Mar 22 17:50:08 2017 peixot_b
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Window.h"
#include <dlfcn.h>

int	main(void)
{
  arcade::Window	w;
  void	*ptr;

  if (!(ptr = dlopen("./sfml.so", RTLD_NOW | RTLD_LAZY)))
    {
      fputs(dlerror(), stderr);
      exit(1);
    }
  while (w.get_Window().isOpen())
    {
      w.event();
      w.refresh();
    }
    return (0);
}
