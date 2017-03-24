//
// Created by vincent.mesquita on 3/19/17.
//

#ifndef CPP_ARCADE_WINDOW_H
#define CPP_ARCADE_WINDOW_H

#include <iostream>
#include <unistd.h>
#include <ncurses/curses.h>
#include <sys/ioctl.h>
#include <ncurses/curses.h>
#include <termios.h>
#include <strings.h>
#include "IWindows.hpp"
#include "NcursesTools.h"

#include <memory>
#include "Vector3d.hpp"
#include "IObject.hpp"
#include "IObserve.hpp"

namespace arcade
{
    class Window{
    public:
        Window(uint64_t height, uint64_t width);
        virtual ~Window();

        virtual bool isOpen() const;
        virtual int32_t getHeight() const;
        virtual int32_t getLenght() const;
        virtual Vector3d const &getSize() const;

        virtual bool event(void);
        virtual arcade::FrameType refresh(void);
        virtual void addObject(std::shared_ptr<arcade::IObject>, Vector3d const &);
        virtual void addObject(std::shared_ptr<arcade::IObject>);
        virtual void moveObject(std::shared_ptr<arcade::IObject>, Vector3d const &);
        virtual void moveObject(std::string, Vector3d const &);
        virtual void destroyObject(std::shared_ptr<arcade::IObject>);

	virtual std::shared_ptr<IEvenement> getEvent(void);
        virtual void removeObserver(std::shared_ptr<arcade::IObserver>&);
      	virtual void registerObserver(std::shared_ptr<arcade::IObserver>&);
    protected:
        Vector3d        _size;
        bool            _isopen;
        WINDOW         *_wmain; //utiliser smartptr
        int32_t         _width;
        int32_t         _height;
        struct termios	_old_ioctl;
        struct termios	_new_ioctl;
        char            _pressed_key[10];
        NcursesTools    _ncursesTools;
//      	std::vector<std::shared_ptr<arcade::IObject>> _objects;

        virtual void	notify(IEvenement const &);
        int             _initTerm(const int i);

    };

}

#endif //CPP_ARCADE_WINDOW_H
