//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_IOBJECT_HPP
#define ARCADE_IOBJECT_HPP

#include <cstdint>
#include <string>

#include "Vector3d.hpp"

namespace arcade
{

  class IObject
  {
    // If a parameters is not used by the object (String for gameObject
    //	will do nothing

   public:
    virtual ~IObject()
    {};

    virtual void		setName(std::string const &) = 0;
    virtual void		setString(std::string const &) = 0;
    virtual void		setPosition(Vector3d const &) = 0;

    virtual std::string const &	getName() const = 0;
    virtual std::string const &	getString() const = 0;
    virtual Vector3d const &	getPosition() const = 0;

    virtual void setVisual(std::string const &) = 0;
  };
};

#endif //ARCADE_IOBJECT_HPP
