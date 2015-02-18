/*
** unsetenv.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:35:15 2010 cerisier mickael
** Last update Wed Apr 28 12:37:30 2010 cerisier mickael
*/

#include <stdlib.h>
#include "globbing.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/strings.h"
#include "lib_includes/free.h"
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"

extern t_global	gl_global;

static int	delete_env(int i, int size)
{
  int		a;
  int		e;
  char		**new_env;

  e = 0;
  a = 0;
  new_env = xmalloc((i - size + 1) * sizeof(*new_env));
  while (e < i)
    {
      if (gl_global.gl_env[e])
	new_env[a++] = gl_global.gl_env[e];
      e++;
    }
  new_env[a] = NULL;
  free(gl_global.gl_env);
  gl_global.gl_env = new_env;
  return (EXIT_SUCCESS);
}

int		my_unsetenv(char **cmd)
{
  int		i;
  int		e;
  int		mem;
  int		size;

  i = -1;
  size = 0;
  cmd = handle_star(cmd, WITH_ENV);
  while (gl_global.gl_env[++i])
    {
      e = 0;
      mem = char_find(gl_global.gl_env[i], '=');
      gl_global.gl_env[i][mem] = '\0';
      while (cmd[++e] && gl_global.gl_env[i])
	if (match(gl_global.gl_env[i], cmd[e]))
	  {
	    free(gl_global.gl_env[i]);
	    gl_global.gl_env[i] = NULL;
	    size++;
	  }
      if (gl_global.gl_env[i])
	gl_global.gl_env[i][mem] = '=';
    }
  free_tab(cmd);
  return (delete_env(i, size));
}
