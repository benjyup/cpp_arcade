//
// Created by vincy on 22/03/17.
//

#ifndef CPP_ARCADE_NCURSESTOOLS_H
#define CPP_ARCADE_NCURSESTOOLS_H

#include <ncurses/curses.h>
#include <ncurses/term.h>
#include <utility>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <string>
#include "IObserve.hpp"

namespace arcade
{

  class NcursesTools {
   public:
    NcursesTools(void);
    ~NcursesTools(void);


    int Refresh(void) const;
    arcade::IEvenement::KeyCode getKey(const char *key) const;
    arcade::IEvenement::KeyCode getKey(const char key) const;

   private:
    std::string                 _term_name;
    std::map<std::string, arcade::IEvenement::KeyCode> _specialKeys;
    std::vector<std::pair<const char *, arcade::IEvenement::KeyCode>> _specialKeysTMP;
    std::map<const char, arcade::IEvenement::KeyCode> _keys;

    arcade::IEvenement::KeyCode _getSpecialKey(const char *key) const;
    bool                        _initTermKeys(void);
    void                        _initSpecialKeys(void);
    void                        _initSpecialKeysTMP(void);
    void                        _initKeys(void);
  };

}

#endif //CPP_ARCADE_NCURSESTOOLS_H
