//
// Created by vincent.mesquita on 3/19/17.
//

#include "Window.hpp"
#include "Object.hpp"

void arcade::Window::_close_window(int)
{
  throw std::runtime_error("CTRL + C");
/*  _ncursesTools.resetTerm(_wmain);*/
}

arcade::Window::Window(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> &objects,
		       uint64_t height,
		       uint64_t width)
	: _size(0, 0),
	  _min_size(0, 0),
	  _isopen(false), _wmain(NULL),
	  _width(width), _height(height),
	  evenement(IEvenement::KeyCode::Key_Undefined),
	  _ncursesTools(), _objects(objects)
{
  // std::cout << std::to_string(_min_size.getY()) + " / " + std::to_string(_min_size.getX()) << std::endl;
  // exit(0);
  if (!(_wmain = _ncursesTools.routine()))
    return;
  signal(SIGINT, _close_window);
  _size.setX(getLenght());
  _size.setY(getHeight());
  checkWindowSize(true);
  bzero(_pressed_key, 10);
  keypad(_wmain, true);
/*  printw(std::to_string(_width).c_str());
  move(1, 0);
  printw(std::to_string(_height).c_str());*/
  _isopen = true;
}

arcade::Window::~Window()
{
  if (_isopen)
    _ncursesTools.resetTerm(_wmain);
  std::cout << "Window supprimée" << std::endl;
}

/* virtual functions of IWindows */

bool 			arcade::Window::isOpen() const
{ return (_isopen); }

int32_t 		arcade::Window::getHeight() const
{ return (getmaxy(_wmain)); }

int32_t 		arcade::Window::getLenght() const
{ return (getmaxx(_wmain)); }

const arcade::Vector3d 	&arcade::Window::getSize() const
{
  return (_size);
}

bool 			arcade::Window::event(void)
{
  evenement.setKeyCode(IEvenement::KeyCode::Key_Undefined);
  bzero(_pressed_key, 10);
  if(read(0, &_pressed_key, 10) == 1 && _pressed_key[0] == 27)
    return (false);
  evenement.setKeyCode(_ncursesTools.getKey(_pressed_key));
  notify(evenement);
  erase();
  return (true);
}

arcade::FrameType 	arcade::Window::refresh()
{
  _size.setX(getLenght());
  _size.setY(getHeight());
  _size.setZ(_size.getX() * _size.getY());
  move(0,0);
  checkWindowSize(false);
  for (auto obj : *_objects)
    _ncursesTools.drawObject(obj);
  _ncursesTools.Refresh();
  clear();
  return (FrameType::GameFrame);
}

void 			arcade::Window::addObject(std::shared_ptr <arcade::IObject> &obj)
{
  _objects->push_back(obj);
}

void 			arcade::Window::addObject(std::shared_ptr <arcade::IObject> &obj, const Vector3d &pos)
{
  obj->setPosition(pos);
  addObject(obj);
}

void 			arcade::Window::moveObject(std::shared_ptr <arcade::IObject> &obj, const Vector3d &pos)
{
  for (auto it : *_objects)
    if (obj == it)
      {
	obj->setPosition(pos);
	return ;
      }
}

void 			arcade::Window::moveObject(std::string name, const Vector3d &pos) // pourquoi pas de std::string & ?
{
  for (auto it : *_objects)
    if (name == it->getName())
      {
	it->setPosition(pos);
	return ;
      }
}

void 			arcade::Window::destroyObject(std::shared_ptr <arcade::IObject> &obj)
{
  auto it = _objects->begin();

  while (it != _objects->end())
    {
      if (*it == obj)
	{
	  _objects->erase(it);
	  return;
	}
      ++it;
    }
}

/* !(virtual functions of IWindows) */

/* virtual functions of IObserved */

void 			arcade::Window::notify(const IEvenement &evenement)
{
  for (auto it : _observers)
      it->getNotified(evenement);
}

std::shared_ptr <arcade::IEvenement> arcade::Window::getEvent()
{
  return (std::shared_ptr<arcade::IEvenement>(NULL));
}

void 			arcade::Window::removeObserver(arcade::IObserver *observer) // pq pas de const
{
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

void 			arcade::Window::registerObserver(arcade::IObserver *observer) //pq pas de const
{
  _observers.push_back(observer);
}

/* !(virtual functions of IObserved) */

bool 			arcade::Window::checkWindowSize(const bool flag)
{
  if (_size.getY() < _min_size.getY() || _size.getX() < _min_size.getX())
    {
      if (flag == true)
	_ncursesTools.resetTerm(_wmain); // reset term if constructor failed
      throw std::runtime_error("The window is too small. " + std::to_string(_min_size.getY()) + " " + std::to_string(_min_size.getX()));
    }
  return false;
}
