/*
** create_history.c for 42sh in /u/all/castel_a/cu/42sh/current/src/ergonomy/history
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat May  8 16:41:22 2010 gianni castellani
** Last update Tue May 11 16:55:20 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"
#include "history.h"
#include "execution.h"
#include "lib_includes/xfunctions.h"
#include "termcaps.h"
#include "jobs.h"
#include "gl_vars.h"

extern t_global		gl_global;

void			remove_first(t_history *hist)
{
  if (hist)
    {
      while (hist->next)
	hist = hist->next;
      if (hist->prev)
	{
	  hist = hist->prev;
	  free(hist->next->data);
	  free(hist->next);
	  hist->next = NULL;
	  gl_global.begin_hist = hist;
	}
    }
}

t_history		*create_history(int fd)
{
  t_history		*cur;
  t_history		*prev;
  char			*str;

  cur = NULL;
  prev = NULL;
  gl_global.begin_hist = NULL;
  while ((str = get_next_line(fd)) != NULL)
    {
      if (gl_global.hist_len >= get_histsize())
	remove_first(cur);
      else
	gl_global.hist_len++;
      cur = xmalloc(sizeof(*cur));
      if (prev == NULL)
	gl_global.begin_hist = cur;
      cur->data = str;
      cur->next = prev;
      if (prev)
	prev->prev = cur;
      prev = cur;
    }
  if (cur != NULL)
    cur->prev = NULL;
  return (cur);
}
