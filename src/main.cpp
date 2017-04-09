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

int 	        main(int ac, char **av)
{
  if (ac != 2)
    return (usage(av[0]));

  std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> objects(new std::vector<std::shared_ptr<arcade::IObject>>);

  try {
      arcade::MainObserver	mo;
      arcade::LibraryManager  	libraryManager;
      arcade::IGraphicalLib   	*graphicalLib = libraryManager.getGraphicalLib(av[1]);
      arcade::IWindows        	*window = graphicalLib->initWindows(objects, 1024, 1024).get();
      arcade::IGameLib        	*gameLib = libraryManager.getGameLib(menu(graphicalLib, libraryManager.getGameLibNames(), objects));
      gameLib->initGame(graphicalLib, &mo, objects);
      graphicalLib->registerObserver(gameLib);
      while (window->event())
	{
	  if (window->refresh() == arcade::FrameType::GameFrame)
	    gameLib->gameTurn();
	}
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  std::cout << objects.use_count() << std::endl;
  return (0);
}
