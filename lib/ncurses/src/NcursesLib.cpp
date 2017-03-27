//
// Created by vincy on 24/03/17.
//

#include "NcursesLib.hpp"
#include "Object.hpp"

namespace arcade
{
  NcursesLib::NcursesLib() : _win() { }
  NcursesLib::~NcursesLib() { }

  std::shared_ptr<arcade::IWindows> &NcursesLib::initWindows(uint64_t height, uint64_t width)
  {
    try {
	_win = std::shared_ptr<Window>(new Window(height, width));
      } catch (std::exception &e) {
	throw std::runtime_error("Not able to open the window : " + std::string(e.what()));
      }
    return (_win);
  }

  void NcursesLib::notify(const IEvenement &) {}

  void NcursesLib::registerObserver(arcade::IObserver *) {}

  std::shared_ptr<IObject> NcursesLib::initObject(const std::string &name, const std::string &filename)
  {
    return(std::shared_ptr<IObject>(new Object(name, filename)));
  }

  std::shared_ptr<arcade::IObject> NcursesLib::initLabel(const std::string &, const std::string &)
  {return(std::shared_ptr<IObject>());}

  std::shared_ptr<IEvenement> NcursesLib::getEvent()
  {return(std::shared_ptr<IEvenement>());}

  std::shared_ptr<arcade::IWindows>& NcursesLib::getWindows() {return (_win);}

  void NcursesLib::removeObserver(arcade::IObserver *) {}

  void* NcursesLib::getHandle() const
  {
   return ((void *) (this));
  }

  ILibrairy *getNewLib(void *)
  {
    return (new NcursesLib());
  }

}

