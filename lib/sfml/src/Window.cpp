//
// Window.cpp for Project-Master in /home/peixot_b/Epitech/Tek2/CPP/Arcade/cpp_arcade/lib/sfml/src
// 
// Made by peixot_b
// Login   <benjamin.peixoto@epitech.eu>
// 
// Started on  Wed Mar 22 17:34:04 2017 peixot_b
// Last update Wed Mar 22 18:52:09 2017 peixot_b
//

#include <string>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Window.h"

arcade::Window::Window() : _size(0,0)
{
  std::cout << "init" << std::endl;
}

arcade::Window::~Window()
{
  std::cout << "Window supprimée" << std::endl;
}

bool arcade::Window::isOpen() const { return (_isopen);}

int32_t arcade::Window::getHeight() const { return (_height);}

int32_t arcade::Window::getLenght() const { return (_width);}

const arcade::Vector3d & arcade::Window::getSize() const
{
  return (_size);
}

bool arcade::Window::event()
{
  return 0;
}

arcade::FrameType arcade::Window::refresh()
{
  return (arcade::FrameType::GameFrame);
}

void arcade::Window::addObject(std::shared_ptr <arcade::IObject>) {}

void arcade::Window::addObject(std::shared_ptr <arcade::IObject>, const Vector3d &) {}

void arcade::Window::moveObject(std::shared_ptr <arcade::IObject>, const Vector3d &) {}

void arcade::Window::moveObject(std::string, const Vector3d &) {}

void arcade::Window::destroyObject(std::shared_ptr <arcade::IObject>) {}

void arcade::Window::notify(const IEvenement &) {}

arcade::IEvenement * arcade::Window::getEvent() { return NULL;}
void arcade::Window::removeObserver(IObserver *) {}
void arcade::Window::registerObserver(IObserver *) {}
