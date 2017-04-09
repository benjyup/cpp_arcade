//
// Menu.cpp for Menu in /home/peixot_b/Epitech/Tek2/CPP/cpp_arcade/src
// 
// Made by Benjamin
// Login   <peixot_b>
// 
// Started on  Sat Apr  8 17:36:34 2017 Benjamin
// Last update Sun Apr  9 14:18:02 2017 vincen_s
//

#include "Menu.hpp"

const unsigned int						arcade::Menu::M_SCALE = 1;
const std::string						arcade::Menu::M_FONT = "./gfx/menu/font";
const std::string						arcade::Menu::M_CURSOR_GFX = "./gfx/menu/cursor";

arcade::Menu::Menu(IGraphicalLib *graphicalLib, const std::vector<std::string> &gameLibNames,
		   std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> &objects)
	:_graphLib(graphicalLib), _gameLibNames(gameLibNames), _objects(objects), _pos(0, 0), _cursor()
{
  _cursor = _graphLib->initObject("cursor", M_CURSOR_GFX);
  _cursor->setPosition(_pos);
  _cursor->setPosition(_pos);
  _graphLib->getWindows()->addObject(_cursor);
  _graphLib->registerObserver(this);
  _printAllNames();
}

arcade::Menu::~Menu()
{
  _graphLib->removeObserver(this);
  _objects->clear();
  _objects.reset();
}

void arcade::Menu::_printAllNames()
{
  std::shared_ptr<arcade::IObject> 	label = _graphLib->initLabel("graphlib", M_FONT);
  arcade::Vector3d			v(15, 0);
  unsigned int				i = 0;

  for (const auto &it : _gameLibNames)
    {
      label.reset();
      label = _graphLib->initLabel("graphlib", M_FONT);
      label->setPosition(v);
      label->setPosition(v);
      label->setString(it.substr(it.find_last_of("_") + 1));
      _graphLib->getWindows()->addObject(label);
      v.setY(v.getY() + M_SCALE);
      i += 1;
    }
  std::cerr << "i = " << i << std::endl;
}

void arcade::Menu::getNotified(IEvenement const &event)
{
  std::cerr << "notified" << std::endl;
  if (event.getAction() == IEvenement::Action::KeyPressDown)
    {
      if (event.getKeyCode() == IEvenement::KeyCode::Key_S)
	_moveDown();
      else if (event.getKeyCode() == IEvenement::KeyCode::Key_Z)
	  _moveUp();
	else if (event.getKeyCode() == IEvenement::KeyCode::Key_D)
	    throw std::string(_getGameLibName());
    }
}

void arcade::Menu::_moveDown(void)
{
  _pos.setY((_pos.getY() + M_SCALE) % (_gameLibNames.size() * M_SCALE));
  _cursor->setPosition(_pos);
  _cursor->setPosition(_pos);
}

void arcade::Menu::_moveUp(void)
{
  _pos.setY(((_pos.getY() - M_SCALE) + _gameLibNames.size()) % (_gameLibNames.size() * M_SCALE));
  _cursor->setPosition(_pos);
  _cursor->setPosition(_pos);
}

std::string arcade::Menu::_getGameLibName(void)
{
  return (_gameLibNames[_pos.getY() / M_SCALE]);
}
