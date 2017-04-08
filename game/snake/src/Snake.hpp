//
// Created by vincent on 03/04/17.
//

#ifndef CPP_ARCADE_SNAKE_HPP
#define CPP_ARCADE_SNAKE_HPP

#include <map>
#include <vector>
#include <ArcadeProtocol.hpp>
#include "IGameLib.hpp"

namespace arcade
{
  class Snake : public IGameLib
  {
   public:

    struct t_snake
    {
      CommandType                                     		ct;
      std::vector<arcade::Position>				body;
    };

    static const std::string					S_MAP_PATH;
    static const std::string					S_HEAD_RESOURCES;
    static const std::string					S_TAIL_RESOURCES;
    static const std::map<arcade::TileType,
	    std::string>					S_TILE_RESOURCES;
    static const std::map<char, arcade::TileType>		S_STRING_TO_TILE;
    static const std::map<CommandType, CommandType>		S_FORBIDEN_COMMAND;
    static const std::map<arcade::IEvenement::KeyCode, CommandType>	S_BINDING;
    static const unsigned long					S_SNAKE_HEAD;
    static const unsigned long					S_DEFAULT_SNAKE_LENGTH;

    Snake(void *handle);
    virtual ~Snake(void);

    /* virtual functions of ILibrary */
    virtual void                                            	*getHandle(void) const;
    virtual std::string const                               	&getName(void) const;
    virtual void 		                                freeSharedData(void);
    /* !virtual functions of ILibrary */

    /* virtual functions of IGameLib */
    virtual void 						initGame(arcade::IGraphicalLib *,
									 arcade::IObserver *,
									 std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject> > >&);
    virtual uint64_t 						getScore(void) const;
    virtual void 						gameTurn(void);
    /* !virtual functions of IGameLib */

    /* virtual functions of IObserver*/
    virtual void 						getNotified(IEvenement const &);
    /* !virtual functions IObserver */

   private:
    std::shared_ptr<std::vector<std::shared_ptr<IObject>>> 	_objects;
    arcade::IGraphicalLib					*_lib;
    arcade::IWindows						*_win;
    std::vector<std::vector<arcade::TileType>>			_map;
    uint64_t 							_score;
    t_snake                                                 	_snake;
    arcade::Vector3d                                        	_map_size;
    void                                                    	*_handle;
    std::string                                             	_lib_name;
    std::mt19937 						_gen;
    std::uniform_int_distribution<int> 				_dis_width;
    std::uniform_int_distribution<int> 				_dis_height;
    std::map<arcade::TileType, std::function<void(void)>> 	_checkMove;
    std::map<arcade::CommandType , std::function<void(void)>> 	_actions;

    /* virtual functions of IGameLib */
    virtual void 						createMap(void);
    virtual void						initGraphicalLib(arcade::IGraphicalLib*);
    /* !virtual functions of IGameLib */

    void							_refreshObjects(void);
    void 							_initSnake(void);
    void 							_initPowerUp(void);
    void 							_dead(void);
    void 							_move(void);
    void 							_powerUp(void);

  };
}

#endif //CPP_ARCADE_SNAKE_HPP
