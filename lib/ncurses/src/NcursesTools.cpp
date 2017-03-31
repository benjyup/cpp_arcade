//
// Created by vincy on 22/03/17.
//

#include <iostream>
#include "NcursesTools.hpp"
#include "Object.hpp"

const std::map<std::string, std::pair<char, short>> arcade::NcursesTools::_colors({{"black", {COLOR_BLACK, 1}}, {"red", {COLOR_RED, 2}},
								{"green", {COLOR_GREEN, 3}}, {"yellow", {COLOR_YELLOW,4}},
								{"blue", {COLOR_BLUE, 5}}, {"magenta", {COLOR_MAGENTA, 6}},
								{"cyan", {COLOR_CYAN, 7}}, {"white", {COLOR_WHITE, 8}}});


	arcade::NcursesTools::NcursesTools()
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

/*void 				arcade::NcursesTools::Wresize(WINDOW *win, int height, int width)
{
  resizeterm(height, width);
  if (wresize(win, height, width) == ERR)
    throw std::runtime_error("Not able to resize the window.");
}*/

WINDOW 				*arcade::NcursesTools::routine()
{
  if (!(_window = initscr()) || _initTerm(1) == false)
    return (NULL);
  start_color();
  use_default_colors();
  throw std::runtime_error("COLOR_PAIRS = " + std::to_string(COLOR_PAIRS));
  init_pair(_colors.at("black").second, _colors.at("black").first, _colors.at("black").first);
  init_pair(_colors.at("red").second, _colors.at("black").first, _colors.at("red").first);
  init_pair(_colors.at("green").second, _colors.at("black").first, _colors.at("green").first);
  init_pair(_colors.at("yellow").second, _colors.at("black").first, _colors.at("yellow").first);
  init_pair(_colors.at("blue").second, _colors.at("black").first, _colors.at("blue").first);
  init_pair(_colors.at("magenta").second, _colors.at("black").first, _colors.at("magenta").first);
  init_pair(_colors.at("cyan").second, _colors.at("black").first, _colors.at("cyan").first);
  init_pair(_colors.at("white").second, _colors.at("black").first, _colors.at("white").first);
  init_pair(500, _colors.at("black").first, _colors.at("white").first);
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
  (void)o;
//  throw std::runtime_error("The configuration file of " + std::to_string(_colors.at(o->getColor()).second));
  try
    {
//      wattron(_window, COLOR_PAIR(_colors.at(o->getColor()).second));
      wattron(_window, COLOR_PAIR(_colors.at(o->getColor()).second));
      mvwprintw(_window, obj->getPosition().getY(), obj->getPosition().getX(), o->getCharacter().c_str());
      wattroff(_window, COLOR_PAIR(_colors.at(o->getColor()).second));
//      wattroff(_window, COLOR_PAIR(_colors.at(o->getColor()).second));
    } catch(const std::exception &e) {
      throw std::runtime_error("The configuration file of " + obj->getName() + " is invalid.");
    }
}
