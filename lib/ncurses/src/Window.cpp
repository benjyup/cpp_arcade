//
// Created by vincent.mesquita on 3/19/17.
//

#include "Window.h"

arcade::Window::Window() : _size(0,0), _isopen(false), _wmain(NULL)
{
    if (!(_wmain = initscr()))
        return ;

    _isopen = true;
    curs_set(0);
    refresh();
    printw(std::to_string(_width).c_str());
    move(1, 0);
    printw(std::to_string(_height).c_str());


/*  printw("Bonjour à tous");
    addch('p');*/
    getch();

}

arcade::Window::~Window()
{
    delwin(_wmain);
    clear();
    curs_set(1);
    endwin();
    std::cout << "Window supprimée" << std::endl;
}

bool arcade::Window::isOpen() const { return false;}

int32_t arcade::Window::getHeight() const { return (_height);}

int32_t arcade::Window::getLenght() const { return (_width);}

const arcade::Vector3d & arcade::Window::getSize() const
{
    return (_size);
}

int arcade::Window::event() { return 0;}

int arcade::Window::refresh()
{
    _width = getmaxx(_wmain);
    _height = getmaxy(_wmain);
    _size.setX(getLenght());
    _size.setY(getHeight());
    _size.setZ(_size.getX() * _size.getY());
    clear();
    return 0;
}

void arcade::Window::addObject(std::shared_ptr <arcade::IObject>) {}

void arcade::Window::addObject(std::shared_ptr <arcade::IObject>, const Vector3d &) {}

void arcade::Window::moveObject(std::shared_ptr <arcade::IObject>, const Vector3d &) {}

void arcade::Window::destroyObject(std::shared_ptr <arcade::IObject>) {}

void arcade::Window::notify(const IEvenement &) {}

arcade::IEvenement * arcade::Window::getEvent() { return NULL;}
void arcade::Window::removeObserver(IObserver *) {}
void arcade::Window::registerObserver(IObserver *) {}