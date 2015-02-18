/*
** my_cursorleft.c for 42sh in /u/all/castel_a/cu/42sh/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 11:38:30 2010 gianni castellani
** Last update Tue May 18 13:22:20 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/xfunctions.h"
#include "termcaps.h"
#include "gl_vars.h"

void			my_cursor_left(__attribute__((unused))
			       char *buf, size_t i[2])
{
  extern t_global	gl_global;
  extern t_termcap	gl_cap;
  int			cpt;

  if (i[0] > 0)
    {
      if ((i[0] + gl_global.prompt_len) % gl_cap.co)
	xtputs(gl_cap.klstr, 1, my_outc);
      else
	{
	  xtputs(gl_cap.kustr, 1, my_outc);
	  cpt = 0;
	  while (cpt < gl_cap.co - 1)
	    {
	      xtputs(gl_cap.krstr, 1, my_outc);
	      cpt++;
	    }
	}
      (i[0])--;
    }
}
