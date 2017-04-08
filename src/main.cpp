//
// Created by vincent on 01/04/17.
//

#include <string>
#include <iostream>
#include "LibraryManager.hpp"

static int      usage(char *bin)
{
  std::cerr << "Usage : " << bin << " GraphicalLibrary" << std::endl;
  return (1);
}

int 	        main(int ac, char **av)
{
  if (ac != 2)
    return (usage(av[0]));

  std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> objects(new std::vector<std::shared_ptr<arcade::IObject>>);

  try {
      arcade::LibraryManager  libraryManager;
      arcade::IGameLib        *gameLib = libraryManager.getGameLib("lib_arcade_nibbler.so");
      arcade::IGraphicalLib   *graphicalLib = libraryManager.getGraphicalLib(av[1]);
      arcade::IWindows        *window = graphicalLib->initWindows(objects, 1024, 1024).get();
      std::cout << "ici = " << std::to_string(objects.use_count()) << std::endl;
      gameLib->initGame(graphicalLib, NULL, objects);
      graphicalLib->registerObserver(gameLib);
      std::cout << "ici = " << std::to_string(objects.use_count()) << std::endl;
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
