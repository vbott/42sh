/*
** no_canonical_mode.c for 42sh in /u/all/castel_a/cu/svn/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Mar 20 14:36:49 2010 gianni castellani
** Last update Tue May 11 12:00:19 2010 gianni castellani
*/

#include <sys/ioctl.h>
#include <termios.h>
#include "lib_includes/xfunctions.h"
#include "termcaps.h"

void			no_canonic_mode(t_termios *newterm,
					t_termios *oldterm, int *termcap)
{
  if (xioctl(0, TIOCGETA, newterm) == -1 && termcap)
    *termcap = 0;
  if (xioctl(0, TIOCGETA, oldterm) == -1 && termcap && *termcap)
    *termcap = 0;
  if (!termcap || *termcap)
    newterm->c_lflag &= ~(ICANON | ECHO | ISIG);
}
