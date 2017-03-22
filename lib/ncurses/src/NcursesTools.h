//
// Created by vincy on 22/03/17.
//

#ifndef CPP_ARCADE_NCURSESTOOLS_H
#define CPP_ARCADE_NCURSESTOOLS_H

#include <ncurses/curses.h>
#include <ncurses/term.h>
#include <cstdlib>
#include <map>
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

    private:
        std::string                 _term_name;
        std::map<char *, arcade::IEvenement::KeyCode> _keysCode;

        arcade::IEvenement::KeyCode _getSpecialKey(const char *key) const;
        bool                        _initTermKeys(void);
        bool                        _initSpecialKeys(void);
    };

}

#endif //CPP_ARCADE_NCURSESTOOLS_H
