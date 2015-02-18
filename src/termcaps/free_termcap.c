/*
** free_termcap.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:30:24 2010 cerisier mickael
** Last update Wed Apr 28 11:30:25 2010 cerisier mickael
*/

#include <stdlib.h>
#include "termcaps.h"

void			free_termcap(void)
{
  extern t_termcap	gl_cap;

  free(gl_cap.term);
}
