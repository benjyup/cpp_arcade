//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_IGRAPHICALLIB_HPP
#define ARCADE_IGRAPHICALLIB_HPP

#include <cstdint>
#include <string>
#include <memory>

#include "IObserve.hpp"
#include "Vector3d.hpp"
#include "IObject.hpp"
#include "IWindows.hpp"
#include "ILibrairy.hpp"

namespace arcade
{
  //
  // GraphicalLib Interface
  //

  class IGraphicalLib : public Arcade::ILibrairy, public IObserved
  {
   public:
    virtual ~IGraphicalLib() {};

    virtual Arcade::ILibrairy::LibType	getType() const {return (Arcade::ILibrairy::LibType ::Graphical);};

    virtual IWindows *			initWindows(uint64_t height = 0,
							  uint64_t lenght = 0) = 0;
    virtual std::shared_ptr<IObject>	initObject(std::string const &) = 0;
    virtual Arcade::IWindows &		getWindows() const = 0;
  };
}

#endif //ARCADE_IGRAPHICALLIB_HPP
