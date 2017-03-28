//
// Created by vincy on 22/03/17.
//

#ifndef CPP_ARCADE_NCURSESTOOLS_H
#define CPP_ARCADE_NCURSESTOOLS_H

#include <exception>
#include <ncurses/curses.h>
#include <ncurses/term.h>
#include <utility>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <sys/ioctl.h>
#include <IObject.hpp>
#include "IObserve.hpp"

namespace arcade
{

  class NcursesTools {
   public:
    NcursesTools(void);
    ~NcursesTools(void);


    /* Ncurses functions */
    int 			Refresh(void) const;
    //void 			Wresize(WINDOW	*, int height, int width);
    /* !Ncurses functions */

    WINDOW 			*routine(void);
    void 			resetTerm(WINDOW *);
    arcade::IEvenement::KeyCode getKey(const char *key) const;
    void 			drawObject(const std::shared_ptr<IObject> obj) const;

   private:
    std::string                 _term_name;
    std::vector<std::pair<const char *, arcade::IEvenement::KeyCode>> _specialKeys;
    std::vector<std::pair<const char *, arcade::IEvenement::KeyCode>> _keys;
    struct termios		_old_ioctl;
    struct termios		_new_ioctl;
    std::map<std::string, int>	_colors;

    //std::map<const char, arcade::IEvenement::KeyCode> _keys;

    bool                        _initTermKeys(void);
    void                        _initKeys(void);
    bool 			_initTerm(const int i);
    WINDOW			*_window;
  };

}

#endif //CPP_ARCADE_NCURSESTOOLS_H
