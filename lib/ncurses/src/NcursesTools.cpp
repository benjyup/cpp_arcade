//
// Created by vincy on 22/03/17.
//

#include <iostream>
#include "NcursesTools.hpp"
#include "Object.hpp"

const std::vector<std::string>	arcade::NcursesTools::NT_DEFAULT_PROPERTIES({"$", "black"});

const std::string					arcade::NcursesTools::NT_BLACK = "black";
const std::string					arcade::NcursesTools::NT_RED = "red";
const std::string					arcade::NcursesTools::NT_GREEN = "green";
const std::string					arcade::NcursesTools::NT_YELLOW = "yellow";
const std::string					arcade::NcursesTools::NT_BLUE = "blue";
const std::string					arcade::NcursesTools::NT_MAGENTA = "magenta";
const std::string					arcade::NcursesTools::NT_CYAN = "cyan";
const std::string					arcade::NcursesTools::NT_WHITE = "white";

const std::map<std::string, std::pair<char, short>> arcade::NcursesTools::NT_COLORS({{NT_BLACK, {COLOR_BLACK, 1}}, {NT_RED, {COLOR_RED, 2}},
										     {NT_GREEN, {COLOR_GREEN, 3}}, {NT_YELLOW, {COLOR_YELLOW,4}},
										     {NT_BLUE, {COLOR_BLUE, 5}}, {NT_MAGENTA, {COLOR_MAGENTA, 6}},
										     {NT_CYAN, {COLOR_CYAN, 7}}, {NT_WHITE, {COLOR_WHITE, 8}}});


arcade::NcursesTools::NcursesTools()
{
  _initTermKeys();
}

arcade::NcursesTools::~NcursesTools() { }

int arcade::NcursesTools::Refresh() const
{
  return (refresh());
}

arcade::IEvenement::KeyCode arcade::NcursesTools::getKey(const char *keyCode) const
{
  arcade::IEvenement::KeyCode key = arcade::IEvenement::KeyCode::Key_Undefined;

  if (!keyCode || !keyCode[0])
    return (key);
  for (auto it : _Keys)
    if (std::strcmp(keyCode, it.first) == 0)
      return (it.second);
  return (key);
}

bool				arcade::NcursesTools::_initTermKeys(void)
{
  char                  	*str;
  int                     	err;

  if (!(str = std::getenv("TERM")))
    return (false);
  _term_name = str;
  if ((setupterm(_term_name.c_str(), 0, &err)) != OK && err != 1)
    return (false);
  _initKeys();
  return (true);
}

void 				arcade::NcursesTools::_initKeys(void)
{
  _Keys.push_back(std::make_pair(tigetstr("kcuu1"), arcade::IEvenement::KeyCode::Key_UP));
  _Keys.push_back(std::make_pair(tigetstr("kcub1"), arcade::IEvenement::KeyCode::Key_LEFT));
  _Keys.push_back(std::make_pair(tigetstr("kcuf1"), arcade::IEvenement::KeyCode::Key_RIGHT));
  _Keys.push_back(std::make_pair(tigetstr("kcud1"), arcade::IEvenement::KeyCode::Key_DOWN));
  _Keys.push_back(std::make_pair("a", arcade::IEvenement::KeyCode::Key_A));
  _Keys.push_back(std::make_pair("d", arcade::IEvenement::KeyCode::Key_D));
  _Keys.push_back(std::make_pair("q", arcade::IEvenement::KeyCode::Key_Q));
  _Keys.push_back(std::make_pair("s", arcade::IEvenement::KeyCode::Key_S));
  _Keys.push_back(std::make_pair("z", arcade::IEvenement::KeyCode::Key_Z));
  for (auto it : _Keys)
    if (it.first == (char *)0 || it.first == (char *)-1)
      throw std::runtime_error("Not able to init the keypad.");
}

WINDOW 				*arcade::NcursesTools::routine()
{
  if (!(_window = initscr()) || _initTerm(1) == false)
    return (NULL);
  start_color();
  use_default_colors();
  init_pair(NT_COLORS.at(NT_BLACK).second, NT_COLORS.at(NT_BLACK).first, NT_COLORS.at(NT_BLACK).first);
  init_pair(NT_COLORS.at(NT_RED).second, NT_COLORS.at(NT_RED).first, NT_COLORS.at(NT_RED).first);
  init_pair(NT_COLORS.at(NT_GREEN).second, NT_COLORS.at(NT_GREEN).first, NT_COLORS.at(NT_GREEN).first);
  init_pair(NT_COLORS.at(NT_YELLOW).second, NT_COLORS.at(NT_YELLOW).first, NT_COLORS.at(NT_YELLOW).first);
  init_pair(NT_COLORS.at(NT_BLUE).second, NT_COLORS.at(NT_BLUE).first, NT_COLORS.at(NT_BLUE).first);
  init_pair(NT_COLORS.at(NT_MAGENTA).second, NT_COLORS.at(NT_MAGENTA).first, NT_COLORS.at(NT_MAGENTA).first);
  init_pair(NT_COLORS.at(NT_CYAN).second, NT_COLORS.at(NT_CYAN).first, NT_COLORS.at(NT_CYAN).first);
  init_pair(NT_COLORS.at(NT_WHITE).second, NT_COLORS.at(NT_WHITE).first, NT_COLORS.at(NT_WHITE).first);

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
      if (o->getType() == Object::ObjectType::Label)
	{
	  wattron(_window, A_BOLD);
	  mvwprintw(_window, obj->getPosition().getY(), obj->getPosition().getX(), o->getString().c_str());
	  wattroff(_window, A_BOLD);
	}
      else
	{
	  wattron(_window, COLOR_PAIR(NcursesTools::NT_COLORS.at(o->getColor()).second));
	  mvwprintw(_window, obj->getPosition().getY(), obj->getPosition().getX(), o->getString().c_str());
	  wattroff(_window, COLOR_PAIR(NcursesTools::NT_COLORS.at(o->getColor()).second));
	}
    } catch(const std::exception &e) {
      throw std::runtime_error("The configuration file of " + obj->getName() + " is invalid.");
    }
}
