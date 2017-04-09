//
// Created by vincent on 01/04/17.
//

#include <string>
#include <iostream>
#include "LibraryManager.hpp"
#include "Menu.hpp"
#include "MainObserver.hpp"

static int      usage(char *bin)
{
  std::cerr << "Usage : " << bin << " GraphicalLibrary" << std::endl;
  return (1);
}

std::string 			menu(arcade::IGraphicalLib *graphicalLib,
					const std::vector<std::string> &gameLibNames,
					std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> &objects)
{
  arcade::Menu 		m(graphicalLib, gameLibNames, objects);
  arcade::IWindows      *window = graphicalLib->getWindows().get();
  std::string		str;

  try {
      while (window->event())
	{
	  window->refresh();
	}
    } catch(const std::string &e) {
      str = e;
    }
  return (str);
}

    int 	        main(int ac, char **av) {
        if (ac != 2)
            return (usage(av[0]));

        try {
            arcade::LibraryManager libraryManager(av[1]);
            libraryManager.gameLoop();
        }

        catch (std::exception &e) {
        }

        return (0);
    }
