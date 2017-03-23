/*
** Window.h for Project-Master in /home/peixot_b/Epitech/Tek2/CPP/Arcade/cpp_arcade/lib/sfml/src
** 
** Made by peixot_b
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Thu Mar 23 13:35:43 2017 peixot_b
** Last update Thu Mar 23 13:35:45 2017 peixot_b
*/

#ifndef WINDOW_H
# define WINDOW_H

#include <iostream>
#include <unistd.h>
#include <memory>
#include "Vector3d.hpp"
#include "IWindows.hpp"

namespace arcade
{
  class Window  : public IWindows {
   public:
    Window();
    virtual				~Window();

    virtual bool			isOpen() const;
    virtual int32_t			getHeight() const;
    virtual int32_t			getLenght() const;
    virtual Vector3d const		&getSize() const;

    virtual bool			event();
    virtual arcade::FrameType		refresh();

    virtual void			addObject(std::shared_ptr<arcade::IObject>, Vector3d const &);
    virtual void			addObject(std::shared_ptr<arcade::IObject>);

    virtual void			moveObject(std::shared_ptr<arcade::IObject>, Vector3d const &);
    virtual void			moveObject(std::string, Vector3d const &);

    virtual void			destroyObject(std::shared_ptr<arcade::IObject>);

    virtual arcade::IEvenement		*getEvent();
    virtual void 			removeObserver(IObserver *);
    virtual void 			registerObserver(IObserver *);

   protected:
    Vector3d				_size;
    bool				_isopen;
    int32_t				_width;
    int32_t				_height;

    virtual void			notify(IEvenement const &);
  };

}

#endif /* !WINDOW_H_ */