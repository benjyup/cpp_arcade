//
// Created by vincent on 01/04/17.
//

#ifndef CPP_ARCADE_LIBRARYMANAGER_HPP
#define CPP_ARCADE_LIBRARYMANAGER_HPP

#include <vector>
#include <string>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdexcept>
#include <iostream>
#include <map>
#include <IGameLib.hpp>
#include "IGraphicalLib.hpp"
#include "IGameLib.hpp"
#include "ILibrairy.hpp"

namespace arcade
{

  typedef arcade::ILibrairy *(*getNewLibFptr)(void*);
//    typedef arcade::IGameLib *(*getNewLibFptr)(void*);

  class LibraryManager
  {
   public:

    static const std::string			LM_GRAPHICAL_LIB_DIRECTORY;
    static const std::string			LM_GAME_LIB_DIRECTORY;
    static const std::string			LM_ARCADE_PREFIX;

    LibraryManager(void);
    ~LibraryManager(void);

    IGraphicalLib                               *getGraphicalLib(const std::string &) const;
    IGameLib                                    *getGameLib(const std::string &) const;
    std::vector<std::string>			getGraphicalLibNames(void) const;
    std::vector<std::string>			getGameLibNames(void) const;

   private:
    std::map<std::string, arcade::ILibrairy*> 	_graphLibraries;
    std::map<std::string, arcade::ILibrairy*> 	_gameLibraries;

    std::map<std::string, arcade::ILibrairy*> _findLibrary(const arcade::ILibrairy::LibType type) const;
    bool _isSharedLibrary(const struct dirent*) const;
    void _displayFoundLibraries(void) const;
  };
}

#endif //CPP_ARCADE_LIBRARYMANAGER_HPP
