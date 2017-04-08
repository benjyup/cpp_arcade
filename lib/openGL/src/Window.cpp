//
// Created by florian on 4/4/17.
//

#include <csignal>
#include "Window.hpp"

float   arcade::Window::SQUARE = 20;

void arcade::Window::_close_window(int)
{
    throw std::runtime_error("CTRL + C");
// reset terminal, close windows, destructeur
}

arcade::Window::Window(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> &objects,
                       uint64_t height,
                       uint64_t width)
        : _size(0, 0),
          _min_size(0, 0),
          _isopen(false),
          _contexte(SDL_GLContext(0)),
          _width(width), _height(height),
          evenement(IEvenement::KeyCode::Key_Undefined),
          _openGltools(), _objects(objects)
{
    std::cout << "bbb\n";
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "aaaa\n";
        SDL_Quit();
        return ;
    }
    _win = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _height, _width,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(_win == 0)
    {
        std::cout << "aaaa\n";
        SDL_Quit();
        return ;
    }
    std::cout << "ccccc\n";
     int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
            printf("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError());
        }
    std::cout << "ccccc\n";
    if (TTF_Init() < 0) // load font
        printf("Can't load ttf lib\n");
    std::cout << "ccccc\n";
    screenSurface = SDL_GetWindowSurface(_win);
    signal(SIGINT, _close_window);
    _size.setX(getLenght());
    _size.setY(getHeight());
    _isopen = true;
}

arcade::Window::~Window() {
    SDL_DestroyWindow(_win);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

/* virtual functions of IWindows */

bool 			arcade::Window::isOpen() const
{ return (_isopen); }

int32_t 		arcade::Window::getHeight() const {
    return (SDL_GetWindowSurface(_win)->h);
}


int32_t 		arcade::Window::getLenght() const {
    return (SDL_GetWindowSurface(_win)->w);
}

const arcade::Vector3d 	&arcade::Window::getSize() const {
    return (_size);
}

void arcade::Window::setMapSize(uint32_t size)
{
    _min_size.setX(size);
    _min_size.setY(size);
    _min_size.setZ(size * size);
}

bool 			arcade::Window::event(void)
{
    evenement.setKeyCode(IEvenement::KeyCode::Key_Undefined);
    while (SDL_PollEvent(&events) == 1) {
        evenement.setKeyCode(_openGltools.getKey(events.type));
        notify(evenement);
    }
    return (true);
}

arcade::FrameType 	arcade::Window::refresh()
{
    _size.setX(getLenght());
    _size.setY(getHeight());
    _size.setZ(_size.getX() * _size.getY());
//    checkWindowSize(false);
//    glClear( GL_COLOR_BUFFER_BIT );
  for (auto obj : *_objects)
  {
      std::cout << "Print object\n";
      _printObject(obj);
  }
    SDL_UpdateWindowSurface(_win);
    SDL_Delay(1);
    //  SDL_GL_SwapWindow(_win);
    return (FrameType::GameFrame);
}

void 			arcade::Window::addObject(std::shared_ptr <arcade::IObject> &obj)
{
    _objects->push_back(obj);
}

void 			arcade::Window::addObject(std::shared_ptr <arcade::IObject> &obj, const Vector3d &pos) {
    obj->setPosition(pos);
    addObject(obj);
}

void 			arcade::Window::moveObject(std::shared_ptr <arcade::IObject> &obj, const Vector3d &pos)
{
    obj->setPosition(pos);
}

void 			arcade::Window::moveObject(std::string name, const Vector3d &pos) // pourquoi pas de std::string & ?
{
    for (auto it : *_objects)
        if (name == it->getName())
        {
            it->setPosition(pos);
            return ;
        }
}

void 			arcade::Window::destroyObject(std::shared_ptr <arcade::IObject> &obj)
{
    auto it = _objects->begin();

    while (it != _objects->end())
    {
        if (*it == obj)
        {
            _objects->erase(it);
            return;
        }
        ++it;
    }
}

void 			arcade::Window::removeObserver(arcade::IObserver *observer) // pq pas de const
{
    auto it = _observers.begin();

    while (it != _observers.end())
    {
        if (*it == observer)
        {
            _observers.erase(it);
            return ;
        }
        ++it;
    }
}

std::shared_ptr<arcade::IEvenement> arcade::Window::getEvent() {
    return (std::make_shared<arcade::Evenement>(evenement)); //dunno
}

void arcade::Window::notify(const IEvenement &evenement) {
    for (auto it : _observers)
        it->getNotified(evenement);
}

void 			arcade::Window::registerObserver(arcade::IObserver *observer) //pq pas de const
{
    _observers.push_back(observer);
}

void                    arcade::Window::_printObject(std::shared_ptr<arcade::IObject> obj)
{
    try
    {
        std::shared_ptr<arcade::Object> objs = std::dynamic_pointer_cast<arcade::Object>(obj);
        if (objs->isTextureOk())
        {
            objs->updateVisual(0);//static_cast<uint32_t>(this->_clock.getElapsedTime().asMilliseconds() / 100));
            std::cout << "Printing " << obj->getTextureFile() << std::endl ;
            SDL_BlitScaled(objs->getSurface(), NULL, screenSurface, &objs->getSpritePos());
        }
    }
    catch (std::bad_cast const &)
    {
        throw std::exception();
    }
}

void            arcade::Window::_printObjects(void)
{
    for (auto & obj : *this->_objects)
        this->_printObject(obj);
}
