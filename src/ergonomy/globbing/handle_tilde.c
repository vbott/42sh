/*
** handle_tilde.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 15:17:14 2010 gianni castellani
** Last update Thu Apr  1 15:17:15 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/env.h"
#include "lib_includes/strings.h"
#include "lib_includes/aff.h"

int		handle_tilde(char **args, int mode)
{
  char		*home;
  char		*mem;

  if ((*args)[0] == '~')
    {
      if ((home = my_getenv("HOME")))
	{
	  mem = *args;
	  *args = my_strcat(NO_FREE, home, &((*args)[1]), 0);
	  if (mode)
	    free(mem);
	  return (1);
	}
      else
	my_puterror("No home directory.\n");
    }
  return (0);
}
