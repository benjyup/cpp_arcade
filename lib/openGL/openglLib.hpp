#ifndef CPP_ARCADE_OPENGLLIB_HPP
#define CPP_ARCADE_OPENGLLIB_HPP

#include "IGraphicalLib.hpp"
#include "IWindows.hpp"
#include "Window.hpp"

namespace arcade
{
    class OpenGlLib : public IGraphicalLib {
    public:
        OpenGlLib(void *handle);
        virtual ~OpenGlLib();

        /* virtual functions of IGraphicalLib */

        virtual std::shared_ptr<arcade::IWindows> &	initWindows(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject> > >&,
                                                                   uint64_t height = 0,
                                                                   uint64_t lenght = 0);
/*        virtual std::shared_ptr<IObject>		initObject(std::string const &, std::string const &);

        virtual std::shared_ptr<arcade::IObject>	initLabel(std::string const &, std::string const &);
        virtual std::shared_ptr<arcade::IWindows> &	getWindows(void);
        virtual void				setVisual(std::shared_ptr<arcade::IObject> &, std::string const &);
*/

        /* !(virtual functions of IGraphicalLib) */

        /* virtual functions of ILibrairy */

/*
        virtual void *		getHandle(void) const;
        virtual std::string const &	getName(void) const;
        virtual LibType		getType(void) const;
        virtual void 		freeSharedData(void);
*/

        /* !(virtual functions of ILibrairy) */

        /* virtual functions of IObserved */

/*
        virtual std::shared_ptr<IEvenement> getEvent(void);
        virtual void registerObserver(arcade::IObserver*);
        virtual void removeObserver(arcade::IObserver*);
*/

        /* !(virtual functions of IObserved) */

    private:
        std::shared_ptr<arcade::IWindows> _win;
        std::string _name;
        std::vector<arcade::IObserver *> _observers;
        void *_handle;
        std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>> > 	_objects;
    };
}

#endif CPP_ARCADE_OPENGLLIB_HPP