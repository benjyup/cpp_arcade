//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_IWINDOWS_HPP
#define ARCADE_IWINDOWS_HPP

#include <memory>
#include "Vector3d.hpp"
#include "IObject.hpp"
#include "IObserve.hpp"

namespace arcade
{
  //
  // Enum to differentiate frame that update the game and
  // frame only to update the display
  //

  enum class FrameType: char
  {
    GameFrame,
    UpdateFrame
  };

  //
  //		Basic Windows Object
  //

  class IWindows: public IObserved
  {
   public:
    virtual ~IWindows(void) {};

    //
    //		Check if windows succesfully opened
    //

    virtual bool		isOpen(void) const = 0;

    //
    //		Getters
    //

    virtual int32_t		getHeight(void) const = 0;
    virtual int32_t		getLenght(void) const = 0;
    virtual Vector3d const &	getSize(void) const = 0;

    //
    //		GameLoop function
    //

    virtual bool		event(void) = 0;
    virtual arcade::FrameType	refresh(void) = 0;

    //
    //		Object gestion functions
    //

    // Create object and/not move

    virtual void		addObject(std::shared_ptr<arcade::IObject>&, Vector3d const &) = 0;
    virtual void		addObject(std::shared_ptr<arcade::IObject>&) = 0;

    // Move object to pos

    virtual void		moveObject(std::shared_ptr<arcade::IObject>&, Vector3d const &) = 0;
    virtual void		moveObject(std::string, Vector3d const &) = 0;

    // Destroy object
    virtual void		destroyObject(std::shared_ptr<arcade::IObject>&) = 0;
  };
};

#endif //ARCADE_IWINDOWS_HPP
