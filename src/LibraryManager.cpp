//
// Created by vincent on 01/04/17.
//

#include "LibraryManager.hpp"

const std::string	arcade::LibraryManager::LM_GRAPHICAL_LIB_DIRECTORY = "./lib/";
const std::string	arcade::LibraryManager::LM_GAME_LIB_DIRECTORY = "./games/";
const std::string	arcade::LibraryManager::LM_ARCADE_PREFIX = "lib_arcade_";

arcade::LibraryManager::LibraryManager() : _graphLibraries(), _gameLibraries()
{
  _graphLibraries = _findLibrary(arcade::ILibrairy::LibType::Graphical);
  _gameLibraries = _findLibrary(arcade::ILibrairy::LibType::Game);
  _displayFoundLibraries();
  std::cout << "------------------------\n" << std::endl;
}

arcade::LibraryManager::~LibraryManager()
{
  void *handle;
  for (auto &it : _gameLibraries)
    if (it.second)
      {
	handle = it.second->getHandle();
	delete it.second;
	dlclose(handle);
      }
  for (auto &it : _graphLibraries)
    if (it.second)
      {
	handle = it.second->getHandle();
	delete it.second;
	dlclose(handle);
      }
}

std::map<std::string, arcade::ILibrairy*> arcade::LibraryManager::_findLibrary(const arcade::ILibrairy::LibType type) const
{
  DIR 						*dir;
  struct dirent 				*dirp;
  std::string 					libraryPath = ((type == arcade::ILibrairy::LibType::Graphical) ?
								    (LM_GRAPHICAL_LIB_DIRECTORY) : (LM_GAME_LIB_DIRECTORY));
  std::map<std::string, arcade::ILibrairy*>	libraries;
  void 						*handle;
  arcade::getNewLibFptr 			sym;
  std::string 					filepath("");

  if (!(dir = opendir(libraryPath.c_str())))
    throw std::runtime_error("Error(" + std::to_string(errno) + ") opening " + libraryPath);
  while ((dirp = readdir(dir)))
    {
      if(_isSharedLibrary(dirp))
	{
	  filepath = libraryPath + dirp->d_name;
	  if (!(handle = dlopen(filepath.c_str(), RTLD_NOW | RTLD_LAZY)) || !(sym = ((arcade::getNewLibFptr)dlsym(handle, "getNewLib"))))
	    throw std::runtime_error(dlerror());
	  libraries[dirp->d_name] = sym(handle);
	}
    }
  (void)closedir(dir);
  return (libraries);
}

bool arcade::LibraryManager::_isSharedLibrary(const struct dirent *dirInfo) const
{
  std::string dirName(dirInfo->d_name);
  std::string extension("");

  if (dirInfo->d_type != DT_REG || dirName.find(LM_ARCADE_PREFIX) != 0)
    return (false);
  try {
      extension = dirName.substr(dirName.find_last_of("."));
    } catch (const std::exception &e) {
      return (false);
    }
  return ((extension == ".so"));
}

void arcade::LibraryManager::_displayFoundLibraries(void) const
{
  if (_graphLibraries.empty())
    std::cout << "Couldn't find any graphical library." << std::endl;
  else
    {
      std::cout << "Graphical libraries found:" << std::endl;
      for (const auto &it : _graphLibraries)
	std::cout << it.first << std::endl;
    }

  if (_gameLibraries.empty())
    std::cout << "\nCouldn't find any game library." << std::endl;
  else
    {
      std::cout << "\nGame libraries found:" << std::endl;
      for (const auto &it : _gameLibraries)
	std::cout << it.first << std::endl;
    }
}

arcade::IGraphicalLib *arcade::LibraryManager::getGraphicalLib(const std::string &libName) const
{
  try {
      return (static_cast<IGraphicalLib*>(_graphLibraries.at(libName)));
    } catch (const std::exception &e) {
      throw std::runtime_error(libName + " doesn't exist.");
    }
}

arcade::IGameLib *arcade::LibraryManager::getGameLib(const std::string &libName) const
{
  try {
      return (static_cast<IGameLib*>(_gameLibraries.at(libName)));
    } catch (const std::exception &e) {
      throw std::runtime_error(libName + " doesn't exist.");
    }
}

std::vector<std::string> arcade::LibraryManager::getGraphicalLibNames() const
{
  std::vector<std::string> v;

  for (const auto &it : _graphLibraries)
    v.push_back(it.first);
  return (v);
}

std::vector<std::string> arcade::LibraryManager::getGameLibNames() const
{
  std::vector<std::string> v;

  for (const auto &it : _gameLibraries)
    v.push_back(it.first);
  return (v);
}
