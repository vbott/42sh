/*
** my_cursordelete.c for 42sh in /u/all/castel_a/cu/42sh/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 11:40:56 2010 gianni castellani
** Last update Wed May 19 15:29:18 2010 gianni castellani
*/

#include <stdlib.h>
#include "termcaps.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "gl_vars.h"

void			my_cursor_delete(char *buf, size_t i[2])
{
  extern t_global	gl_global;
  extern t_termcap	gl_cap;
  size_t		begin;

  if (i[0] < i[1])
    {
      begin = i[0];
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
      begin_cursor(i);
      i[1]--;
    }
}
