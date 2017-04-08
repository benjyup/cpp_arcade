//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_IGRAPHICALLIB_HPP
#define ARCADE_IGRAPHICALLIB_HPP

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

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

    virtual arcade::ILibrairy::LibType		getType(void) const {return (arcade::ILibrairy::LibType::Graphical);};

    //
    //		Initialise a windows of the current librairy
    //

    virtual std::shared_ptr<arcade::IWindows> &	initWindows(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject> > >&,
								   uint64_t height = 1000,
								   uint64_t lenght = 1000) = 0;

    //
    //		Initialise a object of the current librairy
    //

    virtual std::shared_ptr<IObject>		initObject(std::string const &, std::string const &) = 0;

    //
    //		Initialise a label to print text
    //

    virtual std::shared_ptr<arcade::IObject>	initLabel(std::string const &, std::string const &) = 0;

    //
    //		Update a object Visual with the Texture Dump / etc ...
    //

    virtual void				setVisual(std::shared_ptr<arcade::IObject> &, std::string const &) = 0;

    //
    //		Get the windows of this librairy
    //

    virtual std::shared_ptr<arcade::IWindows> &	getWindows(void) = 0;
  };
}

#endif //ARCADE_IGRAPHICALLIB_HPP
