//
// Created by vincy on 22/03/17.
//

#include "NcursesTools.h"

arcade::NcursesTools::NcursesTools() {}

arcade::NcursesTools::~NcursesTools() {}

int arcade::NcursesTools::Refresh() const
{
  return (refresh());
}

arcade::IEvenement::KeyCode arcade::NcursesTools::getKey(const char *) const
{
  return (arcade::IEvenement::KeyCode::Key_A);
}

bool                        arcade::NcursesTools::_initTermKeys(void)
{
  char                    *str;
  int                     err;

  if (!(str = std::getenv("TERM")))
    return (false); // throw exception
  _term_name = str;
  if ((setupterm(_term_name.c_str(), 0, &err)) != OK && err != 1)
    return (false); // throw execption
  return (true);
}

bool arcade::NcursesTools::_initSpecialKeys()
{
  _keysCode[tigetstr("kcub1")] = arcade::IEvenement::KeyCode::Key_LEFT;
  _keysCode[tigetstr("kcuf1")] = arcade::IEvenement::KeyCode::Key_RIGHT;
  _keysCode[tigetstr("kcuu1")] = arcade::IEvenement::KeyCode::Key_UP;
  _keysCode[tigetstr("kcud1")] = arcade::IEvenement::KeyCode::Key_DOWN;
//  _keysCode[tigetstr((char)arcade::IEvenement::KeyCode::Key_A)] = arcade::IEvenement::KeyCode::Key_a;
//  _keysCode[tigetstr((char)arcade::IEvenement::KeyCode::Key_B)] = arcade::IEvenement::KeyCode::Key_a;
  return (true);
}