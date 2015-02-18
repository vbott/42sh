/*
** setenv.c for 42sh in /u/all/bereng_p/cu/rendu/SVN/svn/current/builtins
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sat Mar 20 12:00:44 2010 philippe berenguel
** Last update Wed Apr 28 12:45:52 2010 mickael cerisier
*/

#include <stdlib.h>
#include "parser.h"
#include "builtins.h"
#include "globbing.h"
#include "lib_includes/aff.h"
#include "lib_includes/env.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"

static void		add_value(char *assign, char *value)
{
  int			i;
  char			**cpy;
  extern t_global	gl_global;

  i = 0;
  cpy = xmalloc(sizeof(*gl_global.gl_env) * (len_tab(gl_global.gl_env) + 2));
  while (gl_global.gl_env && gl_global.gl_env[i])
    {
      cpy[i] = gl_global.gl_env[i];
      i++;
    }
  cpy[i] = my_strcat(NO_FREE, assign, "=", value, 0);
  cpy[i + 1] = NULL;
  free(gl_global.gl_env);
  gl_global.gl_env = cpy;
}

static void		replace_value(char *assign, char *value)
{
  int			i;
  extern t_global	gl_global;

  i = 0;
  while (gl_global.gl_env[i] && !my_strccmp(gl_global.gl_env[i], assign, '='))
    i++;
  free(gl_global.gl_env[i]);
  gl_global.gl_env[i] = my_strcat(NO_FREE, assign, "=", value, 0);
}

void			exec_setenv(char **cmd)
{
  int			len;
  char			*str;
  char			*mem;

  len = char_find(cmd[1], '=');
  if (len != -1)
    {
      mem = my_strcdup(cmd[1], '=');
      str = list_in_str(handle_star_list(&cmd[1][len + 1], 0, WITHOUT_ENV));
    }
  else
    {
      mem = cmd[1];
      if (cmd[2])
	str = list_in_str(handle_star_list(cmd[2], 0, WITHOUT_ENV));
      else
	str = NULL;
    }
  if (!my_getenv(mem))
    add_value(mem, str);
  else
    replace_value(mem, str);
  free(str);
  if (len != -1)
    free(mem);
}

int			my_setenv(char **cmd)
{
  int			len;

  if ((len = len_tab(cmd)) > 3)
    {
      my_puterror("setenv: Too many arguments.\n");
      return (EXIT_FAILURE);
    }
  else if (len == 1)
    aff_env(cmd);
  else
    exec_setenv(cmd);
  return (EXIT_SUCCESS);
}
