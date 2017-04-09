//
// Created by vincent on 01/04/17.
//

#include "LibraryManager.hpp"

const std::string	arcade::LibraryManager::LM_GRAPHICAL_LIB_DIRECTORY = "./lib/";
const std::string	arcade::LibraryManager::LM_GAME_LIB_DIRECTORY = "./games/";
const std::string	arcade::LibraryManager::LM_ARCADE_PREFIX = "lib_arcade_";

std::string 			arcade::LibraryManager::menu(arcade::IGraphicalLib *graphicalLib,
                            const std::vector<std::string> &gameLibNames,
                            std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> &objects) {
    arcade::Menu m(graphicalLib, gameLibNames, objects);
    arcade::IWindows *window = graphicalLib->getWindows().get();
    std::string str;

    try {
        while (window->event())
            window->refresh();
    } catch (const std::string &e) {
        str = e;
    }
    for (auto it : (*this->_objs)) {
        window->destroyObject(it);
        std::cerr << "Destroy menu";
    }
    return (str);
}

arcade::LibraryManager::LibraryManager(std::string const &first) : _graphLibraries(), _gameLibraries(),
                                                                   _objs(new std::vector<std::shared_ptr<arcade::IObject> >)
                                                                    , actuallib(0)
{
  _graphLibraries = _findLibrary(arcade::ILibrairy::LibType::Graphical);
  _gameLibraries = _findLibrary(arcade::ILibrairy::LibType::Game);
  _displayFoundLibraries();

    std::cout << "------------------------\n" << std::endl;
    if ((libgraphinuse = getGraphicalLib(first)) == NULL) {
        std::cerr << "fdp";//       throw
    }
    window = libgraphinuse->initWindows(_objs, 1024, 1024);
    libgameinuse = getGameLib(this->menu(libgraphinuse, getGameLibNames(), _objs));
    libgraphinuse->registerObserver(libgameinuse);
    libgraphinuse->registerObserver(this);
}

int         arcade::LibraryManager::gameLoop(void) {

    libgameinuse->initGame(libgraphinuse, this, _objs);
    while (window->event()) {
        if (actuallib == -1){
            _objs->clear();
            std::cerr << "there\n";
            libgameinuse = getGameLib(menu(libgraphinuse, getGameLibNames(), _objs));
            libgameinuse->initGame(libgraphinuse, this, _objs);
            actuallib = 1;
        }
        if (this->window->refresh() == arcade::FrameType::GameFrame)
                this->libgameinuse->gameTurn();
    }
    return (1);
}

void    arcade::LibraryManager::load_menu() {
    libgameinuse->freeSharedData();
    actuallib = -1;
    window->setMapSize(40);
    for (auto it : (*this->_objs)) {
        libgraphinuse->getWindows()->destroyObject(it);
        std::cerr << "Destroy here";
    }
    _objs->clear();
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

void arcade::LibraryManager::getNotified(arcade::IEvenement const &event){
  if (event.getAction() == arcade::IEvenement::Action::LoadGame)
    load_menu();
}