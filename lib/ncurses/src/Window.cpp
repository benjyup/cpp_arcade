//
// Created by vincent.mesquita on 3/19/17.
//

#include "Window.h"

arcade::Window::Window() : _size(0,0), _isopen(false), _wmain(NULL)
{
    // _initTerm(1);
    std::cout << "init" << std::endl;
    if (!(_wmain = initscr()))
        return ;
    std::cout << "init" << std::endl;

    curs_set(0);
    _isopen = true;
    refresh();
    printw(std::to_string(_width).c_str());
    move(1, 0);
    printw(std::to_string(_height).c_str());
    // getch();

/*  printw("Bonjour à tous");
    addch('p');*/
//    getch();
}

arcade::Window::~Window()
{
    delwin(_wmain);
    clear();
    endwin();
    // _initTerm(0);
    curs_set(1);
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
  // c = getch();
    read(0, &c, 1);
   // char c = 'c';
    move(0,0);
    std::string str = "La touche est : " + c;
    erase();
    move(5,5);
    printw("Bonjour");
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

int        arcade::Window::_initTerm(const int i)
{
    if (i == 1)
    {
        if ((ioctl(0, TCGETS, &_old_ioctl)) == -1 ||
            (ioctl(0, TCGETS, &_new_ioctl)) == -1)
            return (-1);
       _new_ioctl.c_lflag &= ~ECHO;
       _new_ioctl.c_lflag &= ~ICANON;
        _new_ioctl.c_cc[VMIN] = 0;
        _new_ioctl.c_cc[VTIME] = 1;
        if ((ioctl(0, TCSETS, &_new_ioctl)) == -1)
            return (-1);
    }
    else
        if ((ioctl(0, TCSETS, &_new_ioctl)) == -1)
            return (-1);
    return (0);
}
