//
// Menu.hpp for Menu in /home/peixot_b/Epitech/Tek2/CPP/cpp_arcade/src
// 
// Made by Benjamin
// Login   <peixot_b>
// 
// Started on  Sat Apr  8 17:21:30 2017 Benjamin
// Last update Sat Apr  8 17:44:03 2017 Benjamin
//

#ifndef MENU_HPP_
# define MENU_HPP_

#include <vector>
#include <memory>
#include <sstream>
#include <fstream>
#include "IGameLib.hpp"
#include "IGraphicalLib.hpp"
#include "IObserve.hpp"

namespace arcade
{
  class Menu : public IObserver
  {
   public:

    static const unsigned int						M_SCALE;
    static const std::string						M_FONT;
    static const std::string						M_CURSOR_GFX;

    Menu(IGraphicalLib *lib,
	 const std::vector<std::string> &,
	 std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> &objects);
    virtual ~Menu(void);
    virtual void getNotified(IEvenement const &);

   private:
    IGraphicalLib							*_graphLib;
    std::vector<std::string>						_gameLibNames;
    std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> 	_objects;
    arcade::Vector3d							_pos;
    std::shared_ptr<arcade::IObject>					_cursor;

    void								_printAllNames(void);
    void								_moveUp(void);
    void								_moveDown(void);
    std::string								_getGameLibName(void);
  };
};

#endif /* !MENU_HPP */
