/*
** my_getenv.c for 42sh in /u/epitech_2014/bereng_p/public/42group/current/libs/env_funcs
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Sat Mar 13 18:44:14 2010 mickael cerisier
** Last update Wed May 12 10:25:52 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/strings.h"
#include "builtins.h"
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"

char			*my_getenv(const char *name)
{
  int			i;
  extern t_global	gl_global;

  i = 0;
  while (gl_global.gl_env && gl_global.gl_env[i])
    {
      if (my_strccmp(name, gl_global.gl_env[i], '='))
	return (&gl_global.gl_env[i][my_strlen(name) + 1]);
      i++;
    }
  return (my_getlocal(name));
}
