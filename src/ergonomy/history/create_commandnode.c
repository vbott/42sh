/*
** create_commandnode.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Mon May 10 14:53:57 2010 gianni castellani
** Last update Tue May 11 12:58:05 2010 gianni castellani
*/

#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "history.h"
#include "gl_vars.h"

extern t_global		gl_global;

void			create_commandnode(void)
{
  t_history		*hist;

  hist = xmalloc(sizeof(*hist));
  hist->data = my_strdup("");
  hist->next = gl_global.history;
  hist->prev = NULL;
  if (gl_global.history)
    {
      gl_global.history->prev = hist;
      gl_global.history = gl_global.history->prev;
    }
  else
    gl_global.history = hist;
}

void			delete_commandnode(void)
{
  if (gl_global.history)
    {
      while (gl_global.history->prev)
	gl_global.history = gl_global.history->prev;
      free(gl_global.history->data);
      if (gl_global.history->next == NULL)
	{
	  free(gl_global.history);
	  gl_global.history = NULL;
	}
      else
	{
	  gl_global.history = gl_global.history->next;
	  free(gl_global.history->prev);
	  gl_global.history->prev = NULL;
	}
    }
}
