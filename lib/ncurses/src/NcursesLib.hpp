//
// Created by vincy on 24/03/17.
//

#ifndef CPP_ARCADE_NCURSESLIB_HPP
#define CPP_ARCADE_NCURSESLIB_HPP

#include <stdexcept>
#include "IGraphicalLib.hpp"
#include "Window.hpp"

namespace arcade
{
  class NcursesLib : public IGraphicalLib
  {
   public:
    NcursesLib(uint64_t height, uint64_t width);
    virtual ~NcursesLib();

    virtual std::shared_ptr<arcade::IWindows> 	&initWindows(uint64_t height = 0,
								  uint64_t lenght = 0);
    virtual std::shared_ptr<IObject>		initObject(std::string const &);
    virtual std::shared_ptr<arcade::IObject>	initLabel(std::string const &);
    virtual IWindows &				getWindows(void) const;

    virtual void *		getHandle(void) const;
    virtual std::string const &	getName(void) const;
    virtual LibType		getType(void) const;
    virtual void 		freeSharedData(void) {};

    virtual std::shared_ptr<IEvenement> getEvent(void);
    virtual void registerObserver(std::shared_ptr<arcade::IObserver>&);
    virtual void removeObserver(std::shared_ptr<arcade::IObserver>&);

   private:
    std::shared_ptr<arcade::IWindows> _win;
  };
}
#endif //CPP_ARCADE_NCURSESLIB_HPP
