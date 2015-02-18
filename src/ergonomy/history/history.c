/*
** historic.c for 42sh in /u/all/castel_a/cu/42sh/current/src/ergonomy/historic
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Apr 17 15:40:52 2010 gianni castellani
** Last update Tue May 18 18:22:00 2010 gianni castellani
*/

#include <unistd.h>
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"

void			erase_line(size_t i[2])
{
  extern t_termcap	gl_cap;
  extern t_global	gl_global;
  size_t		cpt;
  size_t		j[2];

  j[0] = 0;
  j[1] = i[0];
  begin_cursor(j);
  cpt = 0;
  while (cpt < i[1])
    {
      cpt++;
      my_putchar(' ');
      if (!((cpt + gl_global.prompt_len) % gl_cap.co))
	my_putchar('\n');
    }
  i[0] = 0;
  begin_cursor(i);
  i[1] = 0;
}

char			*hist_dup(char *str, size_t len)
{
  char			*ret;
  size_t		cpt;

  ret = xmalloc((len + 1) * sizeof(*ret));
  cpt = 0;
  while (cpt < len)
    {
      ret[cpt] = str[cpt];
      cpt++;
    }
  ret[cpt] = '\0';
  return (ret);
}

void			hist_up(char *buf, size_t i[2])
{
  extern t_global	gl_global;

  if (gl_global.history)
    {
      if (gl_global.history->next != NULL)
	{
	  if (!gl_global.history->prev)
	    {
	      free(gl_global.history->data);
	      gl_global.history->data = hist_dup(buf, i[1]);
	    }
	  erase_line(i);
	  gl_global.history = gl_global.history->next;
	  i[0] = 0;
	  i[1] = 0;
	  add_char(buf, gl_global.history->data, i);
	}
    }
}

void			hist_down(char *buf, size_t i[2])
{
  extern t_global	gl_global;

  if (gl_global.history)
    {
      if (gl_global.history->prev != NULL)
	{
	  erase_line(i);
	  gl_global.history = gl_global.history->prev;
	  i[0] = 0;
	  i[1] = 0;
	  add_char(buf, gl_global.history->data, i);
	}
    }
}

int			get_histsize(void)
{
  int			res;
  char			*local;

  local = my_getlocal("HISTSIZE");
  if (local)
    {
      res = my_atoi(local);
      if (res > 0)
	return (res);
    }
  return (HIST_LIMIT);
}

