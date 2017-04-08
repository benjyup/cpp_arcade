//
// Created by florian on 4/4/17.
//

#ifndef CPP_ARCADE_WINDOWS_HPP
#define CPP_ARCADE_WINDOWS_HPP

#include "openglLib.hpp"
#include "Evenement.hpp"
#include "OpenGltools.hpp"
#include "IWindows.hpp"
#include "Object.hpp"

namespace arcade {
    class Object;

    class Window : public IWindows {
    public:
        Window(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> &, uint64_t height = 1000,
               uint64_t width = 1000);

        virtual ~Window();

        /* virtual functions of IWindows */

        virtual bool isOpen() const;

        virtual int32_t getHeight() const;

        virtual int32_t getLenght() const;

        virtual Vector3d const &getSize() const;

        virtual void setMapSize(uint32_t);

        virtual bool event(void);

        virtual arcade::FrameType refresh(void);

        virtual void addObject(std::shared_ptr<arcade::IObject> &, Vector3d const &);

        virtual void addObject(std::shared_ptr<arcade::IObject> &);

        virtual void moveObject(std::shared_ptr<arcade::IObject> &, Vector3d const &);

        virtual void moveObject(std::string, Vector3d const &);

        virtual void destroyObject(std::shared_ptr<arcade::IObject> &);


        /* !(virtual functions of IWindows) */

        /* virtual functions of IObserved */


        virtual std::shared_ptr<IEvenement> getEvent(void);

        virtual void registerObserver(arcade::IObserver *);

        virtual void removeObserver(arcade::IObserver *);


        /* !(virtual functions of IObserved) */

/*
        bool 	checkWindowSize(const bool); */
        static void _close_window(int signum);

        virtual void notify(IEvenement const &);
        static float SQUARE;

    protected:
        void _printObjects(void);

        void _printObject(std::shared_ptr<arcade::IObject>);

        SDL_Event events;

        Vector3d _size;
        Vector3d _min_size;
        bool _isopen;

        SDL_Window *_win;
        SDL_GLContext _contexte;

        int32_t _width;
        int32_t _height;

        Evenement evenement;

        char _pressed_key[10];
        OpenGltools _openGltools;

        std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> _objects;
        std::vector<arcade::IObserver *> _observers;
        SDL_Surface                     *screenSurface;
    };
}

#endif //CPP_ARCADE_WINDOWS_HPP
