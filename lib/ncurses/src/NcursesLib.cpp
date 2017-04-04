//
// NcursesLib.cpp for  in /home/vincent/rendu/cpp_arcade/lib/ncurses
// 

#include "NcursesLib.hpp"
#include "Object.hpp"

namespace arcade
{
  NcursesLib::NcursesLib(void *handle) : _win(NULL), _name("NcursesLib"), _observers(),
					 _handle(handle) { }

  NcursesLib::~NcursesLib()
  {
    //_objects.reset();
  }

  /* virtual functions of IGraphicalLib */

  std::shared_ptr<arcade::IWindows> &NcursesLib::initWindows(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>> >&objs,
							     uint64_t height,
							     uint64_t width)
  {
    try
      {
	_objects = objs;
	_win = std::shared_ptr<IWindows>(new Window(objs, height, width));
      }
    catch (std::exception &e)
      {
	throw std::runtime_error("Not able to open the window : " + std::string(e.what()));
      }
    return (_win);
  }

  std::shared_ptr<IObject> NcursesLib::initObject(const std::string &name, const std::string &filename)
  {
    return (std::shared_ptr<IObject>(new Object(name, filename)));
  }

  std::shared_ptr<arcade::IObject> NcursesLib::initLabel(const std::string &name, const std::string &filename)
  {return(std::shared_ptr<IObject>(new Label(name, filename)));}

  std::shared_ptr<arcade::IWindows>& NcursesLib::getWindows()
  {
    return (_win);
  }

  void NcursesLib::setVisual(std::shared_ptr<arcade::IObject> &obj, std::string const & filename)
  {
    Object *o = static_cast<Object*>(obj.get());
    if (o->getType() == Object::ObjectType::Label)
      {
	Label *label = static_cast<Label*>(obj.get());
	label->setProperties(filename);
      }
    else
    	o->setProperties(filename);
  }

  /* !(virtual functions of IGraphicalLib) */

  /* virtual functions of IObserved */

  std::shared_ptr<IEvenement> NcursesLib::getEvent()
  {return(std::shared_ptr<IEvenement>());}

  void NcursesLib::notify(const IEvenement &evenement)
  {
    for (auto &it : _observers)
      it->getNotified(evenement);
  }

  void NcursesLib::registerObserver(arcade::IObserver *observer)
  {
    _win->registerObserver(observer);
    _observers.push_back(observer);
  }

  void NcursesLib::removeObserver(arcade::IObserver *observer)
  {
    if (observer == NULL)
      return ;
    auto it = _observers.begin();

    while (it != _observers.end())
      {
	if (*it == observer)
	  {
	    _observers.erase(it);
	    return ;
	  }
	++it;
      }
  }

  /* !(virtual functions of IObserved) */

  /* virtual functions of ILibrairy */

  void* NcursesLib::getHandle() const { return ((void *) (_handle)); }

  std::string const& NcursesLib::getName() const { return (_name); }

  ILibrairy::LibType NcursesLib::getType() const {return (ILibrairy::LibType ::Graphical);}

  void NcursesLib::freeSharedData(void) { }

  /* !(virtual functions of ILibrairy) */


  ILibrairy *getNewLib(void *handle)
  {
    return (new NcursesLib(handle));
  }

}
