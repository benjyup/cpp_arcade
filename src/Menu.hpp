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
  class Menu : public IGameLib, public IObserved
  {
   public:
    Menu(std::vector<arcade::IGameLib*>*);
    virtual ~Menu(void);
    
    void						navigateMenu(int8_t move);
    void						reloadAllObj(void);
    virtual void					initGame(arcade::IGraphicalLib*,
								 std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> &);
    virtual void *					getHandle(void) const;
    virtual const std::string &				getName(void) const;
    virtual void					gameTurn(void);
    virtual uint64_t					getScore(void) const {return (0);};
    virtual void					freeSharedData(void);
    
    virtual void					createMap(void) {};    
    virtual void					getNotified(IEvenement const &evenement);
    virtual void					notify(IEvenement const &evenement);
    virtual std::shared_ptr<IEvenement>			getEvent(void);
    virtual void					registerObserver(arcade::IObserver *);
    virtual void					removeObserver(arcade::IObserver *);
    
    void						sortObjs(void);
    void						initGraphicalLib(arcade::IGraphicalLib*);
    void 						deleteListGame(void);
    void 						printListGame(void);
    void 						updateListGame(void);
    std::shared_ptr<arcade::IObject>			createObject(std::string const &, std::string const &,
								     arcade::Vector3d const &, uint32_t speed = 0);
    std::shared_ptr<arcade::IObject>			createLabel(std::string const &, std::string const &,
								    arcade::Vector3d const &,
								    std::string const & text = "", float scale = 1);
    std::vector<std::shared_ptr<arcade::IObject>>	createBox(std::string const & name,
								  arcade::Vector3d const & start,
								  arcade::Vector3d const & size,
								  bool selected);
    
    protected:
    std::string								_name;
    void *								_handle;
    arcade::IGraphicalLib*						_actualLib;
    std::vector<arcade::IGameLib*>*					_games;
    std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>>	_objects;
    static std::string const						_font;
    std::vector<std::shared_ptr<arcade::IObject> >			_menu;
    int8_t 								_tab;
    std::vector<arcade::IObserver*>					_observateur;   
  };
};

#endif /* !MENU_HPP */
