//
// Created by vincy on 24/03/17.
//

#include "NcursesLib.hpp"
#include "Object.hpp"

namespace arcade
{
  NcursesLib::NcursesLib() : _win(), _name("NcursesLib"), _observers() { }

  NcursesLib::~NcursesLib() { }

  /* virtual functions of IGraphicalLib */

  std::shared_ptr<arcade::IWindows> &NcursesLib::initWindows(uint64_t height, uint64_t width)
  {
    try {
	_win = std::shared_ptr<Window>(new Window(height, width));
      } catch (std::exception &e) {
	throw std::runtime_error("Not able to open the window : " + std::string(e.what()));
      }
    return (_win);
  }

  std::shared_ptr<IObject> NcursesLib::initObject(const std::string &name, const std::string &filename)
  {
    return(std::shared_ptr<IObject>(new Object(name, filename)));
  }

  std::shared_ptr<arcade::IObject> NcursesLib::initLabel(const std::string &, const std::string &)
  {return(std::shared_ptr<IObject>());}

  std::shared_ptr<arcade::IWindows>& NcursesLib::getWindows() {return (_win);}

  /* !(virtual functions of IGraphicalLib) */

  /* virtual functions of IObserved */

  std::shared_ptr<IEvenement> NcursesLib::getEvent()
  {return(std::shared_ptr<IEvenement>());}

  void NcursesLib::notify(const IEvenement &evenement)
  {
    for (auto it : _observers)
      it->getNotified(evenement);
  }

  void NcursesLib::registerObserver(arcade::IObserver *observer)
  {
    _observers.push_back(observer);
  }

  void NcursesLib::removeObserver(arcade::IObserver *observer)
  {
    auto it = _observers.begin();

    while (it != _observers.end())
      {
	if (*it == observer)
	  _observers.erase(it);
	++it;
      }
  }

  /* !(virtual functions of IObserved) */

  /* virtual functions of ILibrairy */

  void* NcursesLib::getHandle() const { return ((void *) (this)); }

  std::string const& NcursesLib::getName() const { return (_name); }

  ILibrairy::LibType NcursesLib::getType() const {return (ILibrairy::LibType ::Graphical);}

  void NcursesLib::freeSharedData(void) { }

  /* !(virtual functions of ILibrairy) */


  ILibrairy *getNewLib(void *)
  {
    return (new NcursesLib());
  }

}

