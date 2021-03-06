/*
** Window.h for Project-Master in /home/peixot_b/Epitech/Tek2/CPP/Arcade/cpp_arcade/lib/sfml/src
** 
** Made by peixot_b
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Thu Mar 23 13:35:43 2017 peixot_b
** Last update Thu Mar 23 13:35:45 2017 peixot_b
*/

#ifndef WINDOW_HPP_
# define WINDOW_HPP_

#include <iostream>
#include <unistd.h>
#include <memory>
#include "Vector3d.hpp"
#include "IWindows.hpp"
#include <SFML/Graphics.hpp>


namespace arcade
{
    class Window  : public IWindows {
    public:
        Window(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>>&, uint64_t height = 0, uint64_t width = 0);
        virtual				                ~Window();

        virtual bool			            isOpen() const;

        virtual int32_t			            getHeight() const;
        virtual int32_t			            getLenght() const;

        virtual sf::RenderWindow const	    &get_Window() const;
        virtual Vector3d const		        &getSize() const;

        void                                setMapSize(uint32_t size);

        virtual bool			            event();
        virtual arcade::FrameType		    refresh();

        virtual void			            addObject(std::shared_ptr<arcade::IObject> &, Vector3d const &);
        virtual void			            addObject(std::shared_ptr<arcade::IObject> &);

        virtual void			            moveObject(std::shared_ptr<arcade::IObject> &, Vector3d const &);
        virtual void			            moveObject(std::string, Vector3d const &);

        virtual void			            destroyObject(std::shared_ptr<arcade::IObject> &);

        virtual std::shared_ptr<IEvenement>	getEvent(void);
        virtual void 			            removeObserver(IObserver *);
        virtual void 			            registerObserver(IObserver *);

        static uint32_t const                               WINSIZE = 1000;
        static uint32_t                                     MAPSIZE;
        static float                                        SIZECELL;
    protected:
        Vector3d								                            _size;
        bool								                                _isopen;
        sf::RenderWindow						                            _window;
        sf::Event								                            _event;
        std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>>	    _objects;
        int32_t								                                _height;
        int32_t								                                _width;
        std::vector<arcade::IObserver*>					                    _observers;
        Vector3d                                                            _min_size;
        sf::Clock                                                           _clock;
        sf::Int32                                                           _calc;

        virtual void					notify(IEvenement const &);
    };

}

#endif /* !WINDOW_HPP_ */