//
// Created by vincy on 22/03/17.
//

#include <iostream>
#include "NcursesTools.h"

arcade::NcursesTools::NcursesTools()
{
  _initTermKeys();
  _initKeys();
  _initSpecialKeysTMP();
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
  for (auto it : _specialKeysTMP)
    {
      std::cout << "(char *)keycode = " << keyCode << " | " << tigetstr("kcuu1") << std::endl;
	if (std::strcmp(keyCode, it.first))
	  return (it.second);
    }
  return (key);
}

arcade::IEvenement::KeyCode arcade::NcursesTools::getKey(const char keyCode) const
{
  arcade::IEvenement::KeyCode key = arcade::IEvenement::KeyCode::Key_Undefined;

  if (_keys.find(keyCode) != _keys.end())
      key = _keys.at(keyCode);
  return (key);
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
  _initSpecialKeys();
  return (true);
}

void arcade::NcursesTools::_initSpecialKeys(void)
{
  _specialKeys[std::string(tigetstr("kcuu1"))] = arcade::IEvenement::KeyCode::Key_UP;
/*  _specialKeys[std::to_string(tigetstr("kcub1"))] = arcade::IEvenement::KeyCode::Key_LEFT;
  _specialKeys[std::to_string(tigetstr("kcuf1"))] = arcade::IEvenement::KeyCode::Key_RIGHT;
  _specialKeys[std::to_string(tigetstr("kcuu1"))] = arcade::IEvenement::KeyCode::Key_UP;
  _specialKeys[std::to_string(tigetstr("kcud1"))] = arcade::IEvenement::KeyCode::Key_DOWN;
  _specialKeys[std::to_string(tigetstr("kf1"))] = arcade::IEvenement::KeyCode::Key_F1;
  _specialKeys[std::to_string(tigetstr("kf2"))] = arcade::IEvenement::KeyCode::Key_F2;
  _specialKeys[std::to_string(tigetstr("kf3"))] = arcade::IEvenement::KeyCode::Key_F3;
  _specialKeys[std::to_string(tigetstr("kf4"))] = arcade::IEvenement::KeyCode::Key_F4;
  _specialKeys[std::to_string(tigetstr("kf5"))] = arcade::IEvenement::KeyCode::Key_F5;
  _specialKeys[std::to_string(tigetstr("kf6"))] = arcade::IEvenement::KeyCode::Key_F6;
  _specialKeys[std::to_string(tigetstr("kf7"))] = arcade::IEvenement::KeyCode::Key_F7;
  _specialKeys[std::to_string(tigetstr("kf8"))] = arcade::IEvenement::KeyCode::Key_F8;
  _specialKeys[std::to_string(tigetstr("kf9"))] = arcade::IEvenement::KeyCode::Key_F9;
  _specialKeys[std::to_string(tigetstr("kf10"))] = arcade::IEvenement::KeyCode::Key_F10;*/
}

void arcade::NcursesTools::_initKeys(void)
{
  _keys['z'] = arcade::IEvenement::KeyCode::Key_Z;
  _keys['q'] = arcade::IEvenement::KeyCode::Key_Q;
  _keys['s'] = arcade::IEvenement::KeyCode::Key_S;
  _keys['d'] = arcade::IEvenement::KeyCode::Key_D;
}

void arcade::NcursesTools::_initSpecialKeysTMP(void)
{
  _specialKeysTMP.push_back(std::make_pair(tigetstr("kcuu1"), arcade::IEvenement::KeyCode::Key_UP));
}