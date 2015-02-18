/*
** env.c for 42sh in /u/all/bereng_p/cu/rendu/SVN/svn/current/builtins
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sat Mar 20 18:39:32 2010 philippe berenguel
** Last update Wed May 12 10:24:09 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/aff.h"
#include "termcaps.h"
#include "parser.h"
#include "execution.h"
#include "jobs.h"
#include "gl_vars.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

static void		init_exec(t_exec *exec)
{
  exec->background = 0;
  exec->pipe = 0;
  exec->fd[0] = -1;
  exec->fd[1] = -1;
  exec->fd[2] = -1;
}

static int		handle_error_env(char **cmd, int *option)
{
  option[0] = 0;
  option[1] = -1;
  if ((option[1] = argument_parser(cmd, option)) == -1)
    return (EXIT_FAILURE);
  if (option[1] == -1)
    return (EXIT_SUCCESS);
  return (-1);
}

static int		exec_cmd_env(char **cmd)
{
  int			data;
  int			option[2];
  char			**mem;
  t_exec		exec;
  extern t_global	gl_global;

  mem = NULL;
  if ((data = handle_error_env(cmd, option)) != -1)
    return (data);
  if (option[0])
    {
      mem = gl_global.gl_env;
      gl_global.gl_env = xmalloc(sizeof(*mem));
      gl_global.gl_env[0] = NULL;
    }
  init_exec(&exec);
  data = cmd_find(&cmd[option[1]], &exec, NULL);
  if (option[0])
    {
      free(gl_global.gl_env);
      gl_global.gl_env = mem;
    }
  return (data);
}

int			aff_env(char **cmd)
{
  int			i;
  extern t_global	gl_global;

  i = 0;
  if (gl_global.gl_env && cmd[1] == NULL)
    {
      while (gl_global.gl_env[i])
	{
	  my_putstr(gl_global.gl_env[i]);
	  my_putchar('\n');
	  i++;
	}
      return (EXIT_SUCCESS);
    }
  else if (gl_global.gl_env)
    return (exec_cmd_env(cmd));
  return (EXIT_FAILURE);
}
