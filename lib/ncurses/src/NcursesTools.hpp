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
    static const std::map<std::string, std::pair<char, short>> 	NT_COLORS;
    static const std::vector<std::string>			NT_DEFAULT_PROPERTIES;
    static const std::string					NT_BLACK;
    static const std::string					NT_RED;
    static const std::string					NT_GREEN;
    static const std::string					NT_YELLOW;
    static const std::string					NT_BLUE;
    static const std::string					NT_MAGENTA;
    static const std::string					NT_CYAN;
    static const std::string					NT_WHITE;
    static const std::string					NT_NONE;

    NcursesTools(void);
    ~NcursesTools(void);


    /* Ncurses functions */
    int 							Refresh(void) const;
    /* !Ncurses functions */

    WINDOW 							*routine(void);
    void 							resetTerm(WINDOW *);
    arcade::IEvenement::KeyCode 				getKey(const char *key) const;
    void 							drawObject(const std::shared_ptr<IObject> obj) const;

   private:
    std::string                 				_term_name;
    std::vector<std::pair<const char *,
	    arcade::IEvenement::KeyCode>> 			_Keys;
    struct termios						_old_ioctl;
    struct termios						_new_ioctl;


    bool                        _initTermKeys(void);
    void                        _initKeys(void);
    bool 			_initTerm(const int i);
    WINDOW			*_window;
  };

}

#endif //CPP_ARCADE_NCURSESTOOLS_H
