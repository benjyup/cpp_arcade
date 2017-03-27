//
// Created by vincent.mesquita on 3/19/17.
//

#ifndef CPP_ARCADE_WINDOW_H
#define CPP_ARCADE_WINDOW_H

#include <iostream>
#include <unistd.h>
#include <ncurses/curses.h>
#include <ncurses/curses.h>
#include <termios.h>
#include <strings.h>

#include "IWindows.hpp"
#include "NcursesTools.h"
#include "Evenement.hpp"

namespace arcade
{
  class Window : public IWindows {
   public:
    Window(uint64_t height, uint64_t width);
    virtual ~Window();

    virtual bool isOpen() const;
    virtual int32_t getHeight() const;
    virtual int32_t getLenght() const;
    virtual Vector3d const &getSize() const;

    virtual bool event(void);
    virtual arcade::FrameType refresh(void);
    virtual void addObject(std::shared_ptr<arcade::IObject>&, Vector3d const &);
    virtual void addObject(std::shared_ptr<arcade::IObject>&);
    virtual void moveObject(std::shared_ptr<arcade::IObject>&, Vector3d const &);
    virtual void moveObject(std::string, Vector3d const &);
    virtual void destroyObject(std::shared_ptr<arcade::IObject>&);

    virtual std::shared_ptr<IEvenement> getEvent(void);
    virtual void registerObserver(arcade::IObserver*);
    virtual void removeObserver(arcade::IObserver*);

    bool 	checkWindowSize(const bool);

   protected:
    Vector3d        	_size;
    Vector3d        	_min_size;
    bool           	_isopen;
    WINDOW         	*_wmain;
    int32_t         	_width;
    int32_t         	_height;
    char            	_pressed_key[10];
    Evenement		evenement;

    NcursesTools    	_ncursesTools;
    std::vector<std::shared_ptr<arcade::IObject>> _objects;
    std::vector<arcade::IObserver*> _observers;

    std::shared_ptr<arcade::IObject> _obj; // à supprimer


    virtual void	notify(IEvenement const &);

  };
}

#endif //CPP_ARCADE_WINDOW_H
