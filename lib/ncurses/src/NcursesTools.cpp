//
// Created by vincy on 22/03/17.
//

#include <iostream>
#include "NcursesTools.h"

arcade::NcursesTools::NcursesTools()
{
  _initTermKeys();
  _initKeys();
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
      throw std::string("MDR");
  std::cout << "pas de nul" << std::endl;
}