//
// Created by vincy on 24/03/17.
//

#include "NcursesLib.hpp"

extern "C"
{


namespace arcade
{
  NcursesLib::NcursesLib(uint64_t height, uint64_t width) : _win(initWindows(height, width)) { }
  NcursesLib::~NcursesLib() { }

  IWindows &NcursesLib::getWindows() const { return (*_win); }

  std::shared_ptr<arcade::IWindows> &NcursesLib::initWindows(uint64_t height, uint64_t width)
  {
    try {
	_win = std::shared_ptr<Window>(new Window(height, width));
      } catch (std::exception &e) {
	throw std::runtime_error("Not able to open the window !");
      }
    return (_win);
  }
}
}
