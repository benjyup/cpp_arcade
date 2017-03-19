//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_IWINDOWS_HPP
#define ARCADE_IWINDOWS_HPP

#include "Vector3d.hpp"
#include "IObject.hpp"
#include "IObserve.hpp"

namespace arcade
{

  // Basic Windows Object

  class IWindows: public IObserved
  {
   public:
    virtual ~IWindows() {};

    virtual bool isOpen() const = 0;
    virtual int32_t getHeight() const = 0;
    virtual int32_t getLenght() const = 0;
    virtual Vector3d const &getSize() const = 0;

    virtual int event() = 0;
    virtual int refresh() = 0;

    virtual void addObject(std::shared_ptr<arcade::IObject>, Vector3d const &) = 0;
    virtual void addObject(std::shared_ptr<arcade::IObject>) = 0;
    virtual void moveObject(std::shared_ptr<arcade::IObject>, Vector3d const &) = 0;
    virtual void destroyObject(std::shared_ptr<arcade::IObject>) = 0;

  };
};

#endif //ARCADE_IWINDOWS_HPP
