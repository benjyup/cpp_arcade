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
    NcursesLib(void);
    virtual ~NcursesLib();

    virtual std::shared_ptr<arcade::IWindows> 	&initWindows(uint64_t height = 0,
								  uint64_t lenght = 0);
    virtual std::shared_ptr<IObject>		initObject(std::string const &, std::string const &);
    virtual std::shared_ptr<arcade::IObject>	initLabel(std::string const &, std::string const &);
    virtual std::shared_ptr<arcade::IWindows> &	getWindows(void);

    virtual void *		getHandle(void) const;
    virtual std::string const &	getName(void) const  {return _name;};
    virtual LibType		getType(void) const {return (arcade::ILibrairy::LibType ::Graphical);};
    virtual void 		freeSharedData(void) {};

    virtual std::shared_ptr<IEvenement> getEvent(void);
    virtual void registerObserver(arcade::IObserver*);
    virtual void removeObserver(arcade::IObserver*);


   private:
    std::shared_ptr<arcade::IWindows> 	_win;
    std::string				_name;

    virtual void notify(IEvenement const &);
  };
}
#endif //CPP_ARCADE_NCURSESLIB_HPP
