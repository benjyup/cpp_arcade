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

//
// GameLib Interface
//

void 		Play();

namespace arcade
{
  class IGameLib : public Arcade::ILibrairy, public IObserver
  {
   public:
    virtual ~IGameLib() {};

    virtual void 			initGame(IGraphicalLib *,
						 std::vector<std::shared_ptr<Arcade::IObject> >*) = 0;
    virtual void			initGraphicalLib(IGraphicalLib*) = 0;

    virtual void 			createObject(std::string const &, std::string const &, Vector3d const &) = 0;

    virtual Arcade::ILibrairy::LibType	getType() const { return (Arcade::ILibrairy::LibType::Game); };
  };
};

#endif //ARCADE_IGAMELIB_HPP
