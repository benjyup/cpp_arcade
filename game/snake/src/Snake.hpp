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

    enum class Direction : int
    {
      NORTH = 1,
      SOUTH,
      EAST,
      WEST,
      UNKNOWN
    };

    struct t_snake
    {
      CommandType                                     		ct;
      uint64_t                                        		length;
      std::vector<arcade::Position>				body;
      arcade::Snake::Direction 					direction;
    };

    static const std::string					S_MAP_PATH;
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
    std::vector<std::vector<arcade::TileType>>			_map;
    uint64_t 							_score;
    t_snake                                                 	_snake;
    arcade::Vector3d                                        	_map_size;
    void                                                    	*_handle;
    std::string                                             	_lib_name;
    std::mt19937 						_gen;
    std::uniform_int_distribution<int> 				_dis_width;
    std::uniform_int_distribution<int> 				_dis_height;

    /* virtual functions of IGameLib */
    virtual void 						createMap(void);
    virtual void						initGraphicalLib(arcade::IGraphicalLib*);
    /* !virtual functions of IGameLib */

    void							_fillTheMap(void);
    void							_refreshObjects(void);
    void 							_initSnake(void);
    void 							_initPowerUp(void);

  };
}

#endif //CPP_ARCADE_SNAKE_HPP
