//
// Created by vincy on 22/03/17.
//

#include <iostream>
#include "NcursesTools.h"
#include "Object.hpp"

arcade::NcursesTools::NcursesTools() :
	_colors({{"black", COLOR_BLACK}, {"red", COLOR_RED},
		 {"green", COLOR_GREEN}, {"yellow", COLOR_YELLOW},
		 {"blue", COLOR_BLUE}, {"magenta", COLOR_MAGENTA},
		 {"cyan", COLOR_CYAN}, {"white", COLOR_WHITE}})
{
  _initTermKeys();
}

arcade::NcursesTools::~NcursesTools() {}

int arcade::NcursesTools::Refresh() const
{
  return (refresh());
}

arcade::IEvenement::KeyCode arcade::NcursesTools::getKey(const char *keyCode) const
{
  arcade::IEvenement::KeyCode key = arcade::IEvenement::KeyCode::Key_Undefined;

  if (!keyCode || !keyCode[0])
    return (key);
  for (auto it : _specialKeys)
    if (std::strcmp(keyCode, it.first) == 0)
      return (it.second);
  for (auto it : _keys)
    if (std::strcmp(keyCode, it.first) == 0)
      return (it.second);
  return (key);
}

bool				arcade::NcursesTools::_initTermKeys(void)
{
  char                  	*str;
  int                     	err;
  std::string			strr;

  if (!(str = std::getenv("TERM")))
    return (false); // throw exception
  _term_name = str;
  if ((setupterm(_term_name.c_str(), 0, &err)) != OK && err != 1)
    return (false); // throw execption
  _initKeys();
  return (true);
}

void 				arcade::NcursesTools::_initKeys(void)
{
  _specialKeys.push_back(std::make_pair(tigetstr("kcuu1"), arcade::IEvenement::KeyCode::Key_UP));
  _specialKeys.push_back(std::make_pair(tigetstr("kcub1"), arcade::IEvenement::KeyCode::Key_LEFT));
  _specialKeys.push_back(std::make_pair(tigetstr("kcuf1"), arcade::IEvenement::KeyCode::Key_RIGHT));
  _specialKeys.push_back(std::make_pair(tigetstr("kcud1"), arcade::IEvenement::KeyCode::Key_DOWN));
  _specialKeys.push_back(std::make_pair("a", arcade::IEvenement::KeyCode::Key_A));
  _specialKeys.push_back(std::make_pair("d", arcade::IEvenement::KeyCode::Key_D));
  _specialKeys.push_back(std::make_pair("q", arcade::IEvenement::KeyCode::Key_Q));
  _specialKeys.push_back(std::make_pair("s", arcade::IEvenement::KeyCode::Key_S));
  _specialKeys.push_back(std::make_pair("z", arcade::IEvenement::KeyCode::Key_Z));
  for (auto it : _specialKeys)
    if (it.first == (char *)0 || it.first == (char *)-1)
      throw std::runtime_error("Not able to init the keypad.");
}

void 				arcade::NcursesTools::Wresize(WINDOW *win, int height, int width)
{
  resizeterm(height, width);
  if (wresize(win, height, width) == ERR)
    throw std::runtime_error("Not able to resize the window.");
}

WINDOW 				*arcade::NcursesTools::routine()
{
  if (!(_window = initscr()) || _initTerm(1) == false)
    return (NULL);
  start_color();
  keypad(_window, true);
  curs_set(0);
  return (_window);
}

bool arcade::NcursesTools::_initTerm(const int i)
{
  if (i == 1)
    {
      if ((ioctl(0, TCGETS, &_old_ioctl)) == -1 ||
	  (ioctl(0, TCGETS, &_new_ioctl)) == -1)
	return (false);
      _new_ioctl.c_lflag &= ~ECHO;
      _new_ioctl.c_lflag &= ~ICANON;
      _new_ioctl.c_cc[VMIN] = 0;
      _new_ioctl.c_cc[VTIME] = 1;
      if ((ioctl(0, TCSETS, &_new_ioctl)) == -1)
	return (false);
    } else
    if ((ioctl(0, TCSETS, &_new_ioctl)) == -1)
      {
	std::cerr << "Error: Not able to reset terminal configuration." << std::endl;
	return (false);
      }
  return (true);
}

void arcade::NcursesTools::resetTerm(WINDOW *window)
{
  _initTerm(0);
  curs_set(1);
  clear();
  delwin(window);
  endwin();
}

void arcade::NcursesTools::drawObject(const std::shared_ptr<arcade::IObject> obj) const
{
  Object *o = static_cast<arcade::Object*>(obj.get());

  try
    {
      init_pair(1, _colors.at(o->getColor()), _colors.at(o->getBackground()));
      wattron(_window, COLOR_PAIR(1));
      mvwprintw(_window, obj->getPosition().getY(), obj->getPosition().getX(), o->getCharacter().c_str());
    } catch(const std::exception &e) {
      throw std::runtime_error("The configuration file of " + obj->getName() + " is invalid.");
    }
  wattroff(_window, COLOR_PAIR(1));
}

