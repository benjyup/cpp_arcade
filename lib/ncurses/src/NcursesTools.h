//
// Created by vincy on 22/03/17.
//

#ifndef CPP_ARCADE_NCURSESTOOLS_H
#define CPP_ARCADE_NCURSESTOOLS_H

#include <ncurses/curses.h>

namespace arcade
{

    class NcursesTools {
    public:
        NcursesTools(void);
        ~NcursesTools(void);


        int Refresh(void) const;

    private:
    };

}

#endif //CPP_ARCADE_NCURSESTOOLS_H
