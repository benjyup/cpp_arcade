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
  //
  //		Object interfaces
  //

  class IObject
  {
   public:
    virtual ~IObject(void) {};

    //
    //		Setters
    //

    virtual void		setName(std::string const &) = 0;
    virtual void		setString(std::string const &) = 0;
    virtual void		setPosition(Vector3d const &) = 0;
    virtual void		setDirection(Vector3d const &) = 0;

    //
    //		Getters
    //

    virtual std::string const &	getName(void) const = 0;
    virtual std::string const &	getString(void) const = 0;
    virtual Vector3d const &	getPosition(void) const = 0;
    virtual Vector3d const &	getDirection(void) const = 0;

    //	String is for label
    //	Name is to differentiate between different object

    //
    //		Set visual following the path given in parameters
    //

    virtual void		setVisual(std::string const &) = 0;

    //
    //		Update Sprite with animation, etc, ...
    //

    virtual void		updateVisual(uint32_t) = 0;
  };
};

#endif //ARCADE_IOBJECT_HPP
