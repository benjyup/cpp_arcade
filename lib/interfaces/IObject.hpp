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

    virtual void			setName(std::string const &) = 0;
    virtual void			setString(std::string const &) = 0;
    virtual void			setTextureFile(std::string const &) = 0;
    virtual void			setPosition(Vector3d const &) = 0;
    virtual void			setDirection(Vector3d const &) = 0;
    virtual void			setSpeed(float) = 0;
    virtual void			setScale(float) = 0;

    //
    //		Getters
    //

    virtual std::string const &		getName(void) const = 0;
    virtual std::string const &		getString(void) const = 0;
    virtual std::string const &		getTextureFile(void) const = 0;
    virtual arcade::Vector3d const &	getPosition (void) const = 0;
    virtual arcade::Vector3d const &	getDirection(void) const = 0;
    virtual float			getSpeed(void) const = 0;
    virtual float			getScale(void) const = 0;

    //
    //		Check if object is still moving
    //

    virtual bool 			isMoving(void) const = 0;
    //
    //		Check if texture is well loaded before drawing
    //

    virtual bool 			isTextureOk(void) const = 0;

    //	String is for label
    //	Name is to differentiate between different object

    //
    //		Set visual following the path given in parameters
    //

    virtual void			setVisual(std::string const &) = 0;

    //
    //		Update Sprite with animation, etc, ...
    //

    virtual void			updateVisual(uint32_t) = 0;
  };
};

#endif //ARCADE_IOBJECT_HPP
