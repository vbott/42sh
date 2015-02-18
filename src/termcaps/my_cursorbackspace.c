/*
** my_cursorbackspace.c for 42sh in /u/all/castel_a/cu/42sh/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 11:40:33 2010 gianni castellani
** Last update Wed May 19 15:28:52 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "termcaps.h"
#include "gl_vars.h"

void			cursor_left(size_t i[2])
{
  extern t_global	gl_global;
  extern t_termcap	gl_cap;
  int			cpt;

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
}

void			my_cursor_backspace(char *buf, size_t i[2])
{
  size_t		begin;
  extern t_global	gl_global;
  extern t_termcap	gl_cap;

  if (i[0] > 0)
    {
      cursor_left(i);
      begin = i[0] - 1;
      while (begin < i[1] - 1)
	{
	  buf[begin] = buf[begin + 1];
	  my_putchar(buf[begin]);
	  if (!((begin + 1 + gl_global.prompt_len) % gl_cap.co))
	    my_putchar('\n');
	  begin++;
	}
      my_putchar(' ');
      if (!((begin + 1 + gl_global.prompt_len) % gl_cap.co))
	my_putchar('\n');
      i[0]--;
      begin_cursor(i);
      i[1]--;
    }
}
