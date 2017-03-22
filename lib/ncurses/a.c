/*
** a.c for  in /home/vincy/rendu/cpp_arcade/lib/ncurses
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincy@epitech.net>
** 
** Started on  Mon Mar 20 21:03:23 2017 vincent.mesquita@epitech.eu
** Last update Mon Mar 20 22:00:31 2017 vincent.mesquita@epitech.eu
*/

#include <curses.h>

int		main(void)
{
  char		c = 'Z';
  initscr();
  curs_set(0);
  /* nodelay(stdscr, true); */
  keypad(stdscr, true);
  while (1)
    {
      /* timeout(1); */
      /* c = getch(); */
      move(10, 10);
      /* if (c == 259) */
      /* 	addch('R'); */
      refresh();
    }
  endwin();
  return (0);
}
