//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_ILIBRAIRY_HPP
#define ARCADE_ILIBRAIRY_HPP

#include <iostream>

namespace arcade
{
  class ILibrairy
  {
   public:
    virtual ~ILibrairy() {};

    enum class LibType
    {
      Graphical,
      Game,
      Unknow = -1
    };

    virtual void *		getHandle() const = 0;
    virtual std::string const &	getName() const = 0;
    virtual LibType		getType() const = 0;
  };

  extern "C"
  {
  Arcade::ILibrairy *getNewLib(void *);
  }
};

#endif //ARCADE_ILIBRAIRY_HPP
