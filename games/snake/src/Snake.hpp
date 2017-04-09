//
// Created by vincent on 03/04/17.
//

#ifndef CPP_ARCADE_SNAKE_HPP
#define CPP_ARCADE_SNAKE_HPP

#include <map>
#include <vector>
#include <Protocol.hpp>
#include <fstream>
#include "../EvenementGame.hpp"
#include "IObserve.hpp"
#include "IGameLib.hpp"

# define S_WIDTH 20
# define S_HEIGHT 20

namespace arcade
{
  class Snake : public IGameLib
  {
   public:

    struct t_snake
    {
      CommandType                                     		ct;
      std::vector<arcade::Position>				body;
      std::vector<std::shared_ptr<arcade::IObject>>		objs;
      std::vector<std::shared_ptr<arcade::IObject>>		objsPowerUp;
    };

    static const unsigned int					S_POWERUP_NBR_DEFAULT;
    static const std::string					S_MAP_PATH;
    static const std::string					S_HEAD_RESOURCES;
    static const std::string					S_TAIL_RESOURCES;
    static const std::string					S_WALL_RESOURCES;
    static const std::string					S_GROUND_RESOURCES;
    static const std::string					S_SNAKE_RESOURCES;
    static const std::string					S_POWERUP_RESOURCES;
    static const std::string					S_TTF_RESOURCES;

    static const std::map<arcade::TileType,
	    std::string>					S_TILE_RESOURCES;
    static const std::map<char, arcade::TileType>		S_STRING_TO_TILE;
    static const std::map<CommandType, CommandType>		S_FORBIDEN_COMMAND;
    static const std::map<arcade::IEvenement::KeyCode, CommandType>	S_BINDING;
    static const unsigned long					S_SNAKE_HEAD;
    static const unsigned long					S_DEFAULT_SNAKE_LENGTH;
    static const uint64_t					S_SCORE_INC;

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

    void             						where_Am_I(void);
    void             						get_map(void);
    void                              				setCt(arcade::CommandType );

   private:
    std::shared_ptr<std::vector<std::shared_ptr<IObject>>> 	_objects;
    arcade::IGraphicalLib					*_lib;
    arcade::IWindows						*_win;
    std::array<std::array<arcade::TileType ,S_WIDTH>, S_HEIGHT>	_map;
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
    std::shared_ptr<arcade::IObject> score;
     arcade::IObserver                                         *_obs;

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
    std::shared_ptr<arcade::IObject>				_createObject(const std::string &name,
										  const std::string &filename,
										  const arcade::Vector3d &pos,
										  float speed);
    std::shared_ptr<arcade::IObject>				_createLabel(const std::string &name,
										 const std::string &filename,
										 const arcade::Vector3d &pos);
    void							_goUp(void);
    void							_goDown(void);
    void							_goLeft(void);
    void							_goRight(void);
    void							_followHead(void);
  };
};

extern "C"
{
void								Play(void);
}

#endif //CPP_ARCADE_SNAKE_HPP
