//
// Created by peixot_b on 05/04/17.
//

#ifndef CPP_ARCADE_SFMLLIB_HPP
#define CPP_ARCADE_SFMLLIB_HPP

#include <stdexcept>
#include "IGraphicalLib.hpp"
#include "IWindows.hpp"
#include "Window.hpp"
#include "Label.hpp"
#include <SFML/Graphics.hpp>

namespace arcade
{
    class SfmlLib : public IGraphicalLib
    {
    public:
        SfmlLib(void *handle);
        virtual ~SfmlLib();

        /* virtual functions of IGraphicalLib */

        virtual std::shared_ptr<arcade::IWindows> &	initWindows(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject> > >&,
                                                                   uint64_t height = 0,
                                                                   uint64_t lenght = 0);
        void                    reloadObject(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> & objs);

        virtual std::shared_ptr<IObject>		    initObject(std::string const &, std::string const &);
        virtual std::shared_ptr<arcade::IObject>	initLabel(std::string const &, std::string const &);
        virtual std::shared_ptr<arcade::IWindows>   &getWindows(void);
        virtual void				                setVisual(std::shared_ptr<arcade::IObject> &, std::string const &);

        /* !(virtual functions of IGraphicalLib) */


        /* virtual functions of ILibrairy */

        virtual void                                *getHandle(void) const;
        virtual std::string const                   &getName(void) const;
        virtual LibType		                        getType(void) const;
        virtual void 		                        freeSharedData(void);

        /* !(virtual functions of ILibrairy) */

        /* virtual functions of IObserved */

        virtual std::shared_ptr<IEvenement>         getEvent(void);
        virtual void                                registerObserver(arcade::IObserver*);
        virtual void                                removeObserver(arcade::IObserver*);

        /* !(virtual functions of IObserved) */

    private:
        std::shared_ptr<arcade::IWindows> 					                _win;
        std::string								                            _name;
        std::vector<arcade::IObserver*>					                    _observers;
        void								                                *_handle;

        std::map<std::string, std::vector<std::string>>			            _visual_save;
        std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>> > 	_objects;

        std::map<std::string, std::shared_ptr<sf::Texture> >        _textureDump;
        std::shared_ptr<sf::Texture>                                &getTexture(std::string const &);

        std::map<std::string, std::shared_ptr<sf::Font> >           _fontDump;
        std::shared_ptr<sf::Font>                                   &getFont(std::string const &);

        virtual void notify(IEvenement const &); // virtual function of IObserved
    };
}

#endif //CPP_ARCADE_SFMLLIB_HPP
