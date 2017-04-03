//
// Created by vincent on 03/04/17.
//

#ifndef CPP_ARCADE_SNAKE_HPP
#define CPP_ARCADE_SNAKE_HPP

#include <unordered_map>
#include <vector>
#include <ArcadeProtocol.hpp>
#include "IGameLib.hpp"

namespace arcade
{
  class Snake : public IGameLib
  {
   public:

    static const std::string					MAP_PATH;
    static const std::unordered_map<arcade::TileType,
	    std::string>					TILE_RESOURCES;

    Snake(void);
    virtual ~Snake(void);

    /* virtual functions of IGameLib */
    virtual void 						initGame(arcade::IGraphicalLib *,
									 std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject> > >&);
    virtual uint64_t 						getScore(void) const;
    virtual void						gameTurn(void);
    /* !virtual functions of IGameLib */

    /* virtual functions of IObserver*/
    virtual void 						getNotified(IEvenement const &);
    /* !virtual functions IObserver */

   private:
    std::shared_ptr<std::vector<std::shared_ptr<IObject>>> 	_objects;
    arcade::ILibrairy						*_lib;
    std::vector<std::vector<arcade::TileType>>			_map;
    uint64_t 							_score;

    /* virtual functions of IGameLib */
    virtual void 						createMap(void);
    virtual void						initGraphicalLib(arcade::IGraphicalLib*);
    /* !virtual functions of IGameLib */

  };
}

#endif //CPP_ARCADE_SNAKE_HPP
