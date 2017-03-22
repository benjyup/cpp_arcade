//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_IGRAPHICALLIB_HPP
#define ARCADE_IGRAPHICALLIB_HPP

#include <cstdint>
#include <string>
#include <memory>

#include "Vector3d.hpp"

#include "IObserve.hpp"
#include "IObject.hpp"
#include "IWindows.hpp"
#include "ILibrairy.hpp"

namespace arcade
{
  //
  //		Graphical librairy Interface
  //			Is a librairy and can be observed by a object IObserver
  //

  class IGraphicalLib : public arcade::ILibrairy, public IObserved
  {
   public:
    virtual ~IGraphicalLib(void) {};

    //
    //		Implementation of getType
    //

    virtual arcade::ILibrairy::LibType	getType(void) const {return (arcade::ILibrairy::LibType ::Graphical);};

    //
    //		Initialise a windows of the current librairy
    //

    virtual arcade::IWindows *		initWindows(uint64_t height = 0,
							  uint64_t lenght = 0) = 0;

    //
    //		Initialise a object of the current librairy
    //

    virtual std::shared_ptr<IObject>	initObject(std::string const &) = 0;

    //
    //		Get the windows of this librairy
    //

    virtual arcade::IWindows &		getWindows(void) const = 0;
  };
}

#endif //ARCADE_IGRAPHICALLIB_HPP
