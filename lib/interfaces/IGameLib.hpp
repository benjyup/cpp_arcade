//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_IGAMELIB_HPP
#define ARCADE_IGAMELIB_HPP

#include <memory>
#include <vector>

#include "IObserve.hpp"
#include "IObject.hpp"
#include "ILibrairy.hpp"
#include "IGraphicalLib.hpp"

extern "C"
{
void		Play(void);
};

namespace arcade
{
  //
  //		Graphical librairy interface
  //			Is a librairy and can observe a object IObserved
  //

  class IGameLib : public arcade::ILibrairy, public IObserver
  {
   protected:

    //
    //		Protected function for initialisation
    //

    virtual void				initGraphicalLib(arcade::IGraphicalLib*) = 0;

    //
    //		Protected function for initialisation of the game map
    //

    virtual void 				createMap(void) = 0;
   public:
    virtual ~IGameLib(void) {};

    //
    //		Game initialisation function
    //

    virtual void 				initGame(arcade::IGraphicalLib *,
							 std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject> > >&) = 0;

    //
    //		Getter for score on game
    //

    virtual uint64_t 				getScore(void) const = 0;

    //
    //		Implementation of getType
    //

    virtual arcade::ILibrairy::LibType		getType(void) const { return (arcade::ILibrairy::LibType::Game); };

    //
    //		Function to update the game and m
    //

    virtual void				gameTurn(void) = 0;
  };
};

#endif //ARCADE_IGAMELIB_HPP
