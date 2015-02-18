/*
** delete_first_node.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Tue May 11 16:24:38 2010 gianni castellani
** Last update Sun May 23 17:05:16 2010 gianni castellani
*/

#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"

void		delete_first_node(void)
{
  extern t_global	gl_global;

  gl_global.hist_len--;
  if (gl_global.begin_hist)
    {
      if (gl_global.begin_hist->prev)
	{
	  gl_global.begin_hist = gl_global.begin_hist->prev;
	  free(gl_global.begin_hist->next->data);
	  free(gl_global.begin_hist->next);
	  gl_global.begin_hist->next = NULL;
	}
      else
	{
	  free(gl_global.begin_hist->data);
          free(gl_global.begin_hist);
          gl_global.begin_hist = NULL;
	  gl_global.history = NULL;
	}
    }
}
