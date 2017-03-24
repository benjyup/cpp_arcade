//
// Created by vincy on 24/03/17.
//

#include "NcursesLib.hpp"

namespace arcade
{
  NcursesLib::NcursesLib(uint64_t height, uint64_t width) : _win(initWindows(height, width)) { }
  NcursesLib::~NcursesLib() { }

  IWindows & NcursesLib::getWindows() const { return (*_win); }

}