/*
** init_cap.c for 42sh in /u/all/castel_a/cu/svn/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Mar 20 11:51:25 2010 gianni castellani
** Last update Wed May 19 19:43:52 2010 gianni castellani
*/

#include <stdlib.h>
#include <termcap.h>
#include "lib_includes/xfunctions.h"
#include "termcaps.h"
#include "lib_includes/env.h"
#include "lib_includes/strings.h"

void			init_cap(int *termcap)
{
  char			*str;
  extern t_termcap	gl_cap;

str = my_getenv("TERM");
  gl_cap.term = my_strcat(NO_FREE, str, "-noapp", 0);
 if (tgetent(gl_cap.bp, gl_cap.term) == -1)
  tgetent(gl_cap.bp, str);
  if (!(gl_cap.kbstr = tgetstr("kb", (char **)&gl_cap.area)))
    {
     if (tgetent(gl_cap.bp, "linux") == -1)
		*termcap = 0;
      gl_cap.kbstr = xtgetstr("kb", (char **)&gl_cap.area);
    }
  if (*termcap)
    {
      gl_cap.kDstr = xtgetstr("kD", (char **)&gl_cap.area);
      gl_cap.clstr = xtgetstr("cl", (char **)&gl_cap.area);
      gl_cap.kustr = xtgetstr("ku", (char **)&gl_cap.area);
      gl_cap.kdstr = xtgetstr("kd", (char **)&gl_cap.area);
      gl_cap.klstr = xtgetstr("kl", (char **)&gl_cap.area);
      gl_cap.krstr = xtgetstr("kr", (char **)&gl_cap.area);
      gl_cap.khstr = xtgetstr("kh", (char **)&gl_cap.area);
      gl_cap.kestr = xtgetstr("@7", (char **)&gl_cap.area);
      gl_cap.cestr = xtgetstr("ce", (char **)&gl_cap.area);
    }
}
