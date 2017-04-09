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
    freeSharedData();
    //_objects.reset();
  }

  /* virtual functions of IGraphicalLib */

  std::shared_ptr<arcade::IWindows> &NcursesLib::initWindows(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>> >&objs,
							     uint64_t height,
							     uint64_t width)
  {
    try
      {
	if (objs && objs->size() != 0)
	  _reloadObject(objs);
	_objects = objs;
//	_win = std::shared_ptr<IWindows>(new Window(objs, height, width));
	_win = std::make_shared<Window>(objs, height, width);
	for (const auto &it : _observers)
	  _win->registerObserver(it);
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
    if (_win != NULL)
      _win->registerObserver(observer);
    //_observers.push_back(observer);
  }

  void NcursesLib::removeObserver(arcade::IObserver *observer)
  {
    _win->removeObserver(observer);
  }

  /* !(virtual functions of IObserved) */

  /* virtual functions of ILibrairy */

  void* NcursesLib::getHandle() const { return ((void *) (_handle)); }

  std::string const& NcursesLib::getName() const { return (_name); }

  ILibrairy::LibType NcursesLib::getType() const {return (ILibrairy::LibType ::Graphical);}

  void NcursesLib::freeSharedData(void)
  {
    for (auto *it : _observers)
      removeObserver(it);
    if (_objects)
      _objects->clear();
    _objects.reset();
  }

  /* !(virtual functions of ILibrairy) */


  ILibrairy *getNewLib(void *handle)
  {
    return (new NcursesLib(handle));
  }

  void NcursesLib::_reloadObject(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>> >&objs)
  {
    std::vector<std::shared_ptr<arcade::IObject>>	obj_tmp;
    int i = 0;

    for (const auto &it : *objs)
      {
	if (it->getString().empty())
	  obj_tmp.push_back(initObject(it->getName(), it->getTextureFile()));
	else
	  obj_tmp.push_back(initLabel(it->getName(), it->getTextureFile()));
	obj_tmp.back()->setScale(it->getScale());
	obj_tmp.back()->setPosition(it->getPosition());
	obj_tmp.back()->setSpeed(it->getSpeed());
	obj_tmp.back()->setDirection(it->getDirection());
	obj_tmp.back()->setString(it->getString());
	i += 1;
      }
    objs->clear();
    for (const auto &it : obj_tmp)
      {
	objs->push_back(it);
      }
    //throw std::runtime_error("je passe ici" + std::to_string(i));
  }
}
