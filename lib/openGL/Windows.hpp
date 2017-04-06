//
// Created by florian on 4/4/17.
//

#ifndef CPP_ARCADE_WINDOWS_HPP
#define CPP_ARCADE_WINDOWS_HPP

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <vector>
#include <string>
#include "IWindows.hpp"
#include "Evenement.hpp"
#include "OpenGltools.hpp"

namespace arcade {
    class Window : public IWindows {
    public:
        Window(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> &, uint64_t height = 0,
               uint64_t width = 0);

        virtual ~Window();

        /* virtual functions of IWindows */

        virtual bool isOpen() const;
        virtual int32_t getHeight() const;
        virtual int32_t getLenght() const;
        virtual Vector3d const &getSize() const;


        virtual void setMapSize(uint32_t);
        virtual bool event(void);
        virtual arcade::FrameType refresh(void);
        virtual void addObject(std::shared_ptr<arcade::IObject>&, Vector3d const &);
        virtual void addObject(std::shared_ptr<arcade::IObject>&);
        virtual void moveObject(std::shared_ptr<arcade::IObject>&, Vector3d const &);
        virtual void moveObject(std::string, Vector3d const &);
        virtual void destroyObject(std::shared_ptr<arcade::IObject>&);


        /* !(virtual functions of IWindows) */

        /* virtual functions of IObserved */


/       virtual std::shared_ptr<IEvenement> getEvent(void);
        virtual void registerObserver(arcade::IObserver*);
        virtual void removeObserver(arcade::IObserver*);


        /* !(virtual functions of IObserved) */

/*
        bool 	checkWindowSize(const bool); */
        static void _close_window(int signum);

        virtual void notify(IEvenement const &);

    protected:
        SDL_Window *_win;
        SDL_GLContext _contexte;
        Evenement evenement;
        SDL_Event events;

        Vector3d _size;
        Vector3d _min_size;
        bool _isopen;
        int32_t _width;
        int32_t _height;
        char _pressed_key[10];
        OpenGltools _OpenGltools;

        std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> _objects;
        std::vector<arcade::IObserver *> _observers;

        std::shared_ptr<arcade::IObject> _obj; // à supprimer


    };
}

#endif //CPP_ARCADE_WINDOWS_HPP
