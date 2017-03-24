//
// Created by vincy on 24/03/17.
//

#ifndef CPP_ARCADE_NCURSESLIB_HPP
#define CPP_ARCADE_NCURSESLIB_HPP

#include "IGraphicalLib.hpp"

namespace arcade
{
  class NcursesLib : public IGraphicalLib
  {
   public:
    NcursesLib(uint64_t height, uint64_t width);
    virtual ~NcursesLib();

    virtual arcade::IWindows *			initWindows(uint64_t height = 0,
								uint64_t lenght = 0);
    virtual std::shared_ptr<IObject>		initObject(std::string const &);
    virtual std::shared_ptr<arcade::IObject>	initLabel(std::string const &);
    virtual IWindows &				getWindows(void) const;

   private:
    IWindows				*_win;
  };
}

#endif //CPP_ARCADE_NCURSESLIB_HPP
