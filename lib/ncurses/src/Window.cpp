//
// Created by vincent.mesquita on 3/19/17.
//

#include "Window.h"

arcade::Window::Window() : _size(0,0), _isopen(false), _wmain(NULL)
{
    if (!(_wmain = initscr()))
        return ;

    _isopen = true;
    //nocbreak();
    refresh();
    printw(std::to_string(_width).c_str());
    move(1, 0);
    printw(std::to_string(_height).c_str());


/*  printw("Bonjour à tous");
    addch('p');*/
//    getch();
}

arcade::Window::~Window()
{
    delwin(_wmain);
    clear();
    curs_set(1);
    cbreak();
    endwin();
    std::cout << "Window supprimée" << std::endl;
}

bool arcade::Window::isOpen() const { return (_isopen);}

int32_t arcade::Window::getHeight() const { return (_height);}

int32_t arcade::Window::getLenght() const { return (_width);}

const arcade::Vector3d & arcade::Window::getSize() const
{
    return (_size);
}

int arcade::Window::event()
{
    char c;
    //char c = getch();
    read(0, &c, 1);
//    char c = 'c';
    move(0,0);
    std::string str = "La touche est : " + c;
    erase();
    addch(c);
    //   printw(str.c_str());
    return 0;
}

int arcade::Window::refresh()
{
    _width = getmaxx(_wmain);
    _height = getmaxy(_wmain);
    _size.setX(getLenght());
    _size.setY(getHeight());
    _size.setZ(_size.getX() * _size.getY());
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

void        arcade::Window::initTerm()
{

}