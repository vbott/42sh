/*
** free_bindkey.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:30:01 2010 cerisier mickael
** Last update Mon May 17 18:05:46 2010 gianni castellani
*/

#include <stdlib.h>
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"

void			free_bindkey(void)
{
  t_bindkey		*mem;
  extern t_global	gl_global;

  while (gl_global.gl_bindkey)
    {
      mem = gl_global.gl_bindkey;
      gl_global.gl_bindkey = gl_global.gl_bindkey->next;
      if (mem->exec != NULL)
	free(mem->exec);
      free(mem);
    }
}
