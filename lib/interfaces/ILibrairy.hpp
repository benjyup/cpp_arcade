//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_ILIBRAIRY_HPP
#define ARCADE_ILIBRAIRY_HPP

#include <iostream>

namespace arcade
{

  //
  //		Game/Graphical Librairy Interfaces
  //

  class ILibrairy
  {
   public:
    virtual ~ILibrairy(void) {};

    //
    //		Enum for the lib type
    //

    enum class LibType
    {
      Graphical,
      Game,
      Unknow = -1
    };

    //
    //		Getters
    //

    virtual void *		getHandle(void) const = 0;
    virtual std::string const &	getName(void) const = 0;
    virtual LibType		getType(void) const = 0;
  };

  //
  //		Librairy entry point
  //

  extern "C"
  {
  arcade::ILibrairy *getNewLib(void *);
  }
};

#endif //ARCADE_ILIBRAIRY_HPP
