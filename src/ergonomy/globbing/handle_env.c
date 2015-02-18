/*
** handle_env.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Tue May 11 15:09:34 2010 cerisier mickael
** Last update Tue May 11 15:09:34 2010 cerisier mickael
*/

#include <stdlib.h>
#include "globbing.h"
#include "gl_vars.h"
#include "lib_includes/strings.h"

extern t_global	gl_global;

t_list		*add_list_env(char *str, t_list *list)
{
  int		i;
  int		e;

  i = 0;
  while (gl_global.gl_env[i] != NULL)
    {
      e = char_find(gl_global.gl_env[i], '=');
      if (e != -1)
	gl_global.gl_env[i][e] = '\0';
      if (match(gl_global.gl_env[i], str))
	list = add_list(my_strdup(gl_global.gl_env[i]), list);
      if (e != -1)
	gl_global.gl_env[i][e] = '=';
      i++;
    }
  return (list);
}
