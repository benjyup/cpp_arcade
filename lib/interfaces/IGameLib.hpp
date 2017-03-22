//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_IGAMELIB_HPP
#define ARCADE_IGAMELIB_HPP

#include <memory>

#include "IObserve.hpp"
#include "IObject.hpp"
#include "ILibrairy.hpp"
#include "IGraphicalLib.hpp"

void 		Play(void);

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

    virtual void				initGraphicalLib(IGraphicalLib*) = 0;

    //
    //		Protected function for initialisation of the game map
    //

    virtual void 				createMap(void) = 0;
   public:
    virtual ~IGameLib(void) {};

    //
    //		Game initialisation function
    //

    virtual void 				initGame(IGraphicalLib *,
							 std::vector<std::shared_ptr<arcade::IObject> >*) = 0;

    //
    //		Create a object and add it to the game (used most likely internely)
    //

    virtual std::shared_ptr<arcade::IObject>	createObject(std::string const &, std::string const &, Vector3d const &) = 0;

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
