//
// Created by vincent.mesquita on 3/19/17.
//

#include "Window.hpp"

arcade::Window::Window(uint64_t height, uint64_t width) : _size(0, 0), _isopen(false), _wmain(NULL),
							  _width(width), _height(height), _ncursesTools(), _objects()
{
  (void) height;
  (void) width;

  if (!(_wmain = initscr()) || _initTerm(1) == -1)
    return;
  bzero(_pressed_key, 10);
  keypad(_wmain, true);
  curs_set(0);
  _isopen = true;
  refresh();
  printw(std::to_string(_width).c_str());
  move(1, 0);
  printw(std::to_string(_height).c_str());
}

arcade::Window::~Window()
{
  delwin(_wmain);
  clear();
  endwin();
  _initTerm(0);
  curs_set(1);
  std::cout << "Window supprimée" << std::endl;
}

bool arcade::Window::isOpen() const
{ return (_isopen); }

int32_t arcade::Window::getHeight() const
{ return (_height); }

int32_t arcade::Window::getLenght() const
{ return (_width); }

const arcade::Vector3d &arcade::Window::getSize() const
{
  return (_size);
}

bool arcade::Window::event(void)
{
  static int i = 0;

  bzero(_pressed_key, 10);
  read(0, &_pressed_key, 10);
  move(0, 0);
  std::string str;
  if (_ncursesTools.getKey(_pressed_key) != arcade::IEvenement::KeyCode::Key_Undefined)
    str = "La touche est : " + std::to_string(i++) + " c =|" + "KEY_A" + "|";
  else
    str = "La touche est : " + std::to_string(i++) + " c =|" + _pressed_key + "|";
  erase();
  move(5, 5);
  printw(str.c_str());
  return (false);
}

arcade::FrameType arcade::Window::refresh()
{
  _width = getmaxx(_wmain);
  _height = getmaxy(_wmain);
  _size.setX(getLenght());
  _size.setY(getHeight());
  _size.setZ(_size.getX() * _size.getY());
  _ncursesTools.Refresh();
  return (FrameType::GameFrame);
}

void arcade::Window::addObject(std::shared_ptr <arcade::IObject> obj)
{
  _objects.push_back(obj);
}

void arcade::Window::addObject(std::shared_ptr <arcade::IObject>, const Vector3d &)
{}

void arcade::Window::moveObject(std::shared_ptr <arcade::IObject>, const Vector3d &)
{}

void arcade::Window::moveObject(std::string, const Vector3d &)
{

}

void arcade::Window::destroyObject(std::shared_ptr <arcade::IObject> obj)
{
  auto it = _objects.begin();

  while (it != _objects.end())
    {
      if (*it == obj)
	{
	  _objects.erase(it);
	  return;
	}
      ++it;
    }
}

void arcade::Window::notify(const IEvenement &)
{}

std::shared_ptr <arcade::IEvenement> arcade::Window::getEvent()
{
  return (std::shared_ptr<arcade::IEvenement>(NULL));
}

void arcade::Window::removeObserver(std::shared_ptr <arcade::IObserver> &)
{}

int arcade::Window::_initTerm(const int i)
{
  if (i == 1)
    {
      if ((ioctl(0, TCGETS, &_old_ioctl)) == -1 ||
	  (ioctl(0, TCGETS, &_new_ioctl)) == -1)
	return (-1);
      _new_ioctl.c_lflag &= ~ECHO;
      _new_ioctl.c_lflag &= ~ICANON;
      _new_ioctl.c_cc[VMIN] = 0;
      _new_ioctl.c_cc[VTIME] = 1;
      if ((ioctl(0, TCSETS, &_new_ioctl)) == -1)
	return (-1);
    } else
    if ((ioctl(0, TCSETS, &_new_ioctl)) == -1)
      return (-1);
  return (0);
}

void arcade::Window::registerObserver(std::shared_ptr<arcade::IObserver>& e) { (void)e;}
