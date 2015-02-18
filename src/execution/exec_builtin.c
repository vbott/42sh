/*
** exec_builtin.c for 42sh in /home/snap/projects/42sh/current
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Thu May  6 04:26:38 2010 botton vivien
** Last update Thu May  6 04:26:38 2010 botton vivien
*/

#include <unistd.h>
#include "parser.h"
#include "execution.h"
#include "builtins.h"
#include "jobs.h"
#include "termcaps.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

static const t_builtin		gl_builtins[] = {
  {"env", aff_env},
  {"cd", cd},
  {"echo", echo},
  {"setenv", my_setenv},
  {"unsetenv", my_unsetenv},
  {"jobs", jobs},
  {"fg", fg},
  {"bg", bg},
  {"exit", quit},
  {"bindkey", bind_key},
  {"history", history},
  {"alias", my_alias},
  {"unalias", unalias},
  {"source", source},
  {"set", set},
  {"unset", unset},
  {NULL, NULL}
};

int		exec_builtin(char **cmd, t_exec *exec, int i)
{
  int		fd[3];

  fd[0] = (exec->fd[0] != -1) ? xdup(STDIN_FILENO) : -1;
  fd[1] = (exec->fd[1] != -1) ? xdup(STDOUT_FILENO) : -1;
  fd[2] = (exec->fd[2] != -1) ? xdup(STDERR_FILENO) : -1;
  dup_fd(exec->fd);
  i = gl_builtins[i].func(cmd);
  if (exec->fd[0] != -1)
    {
      xdup2(fd[0], STDIN_FILENO);
      xclose(fd[0]);
    }
  if (exec->fd[1] != -1)
    {
      xdup2(fd[1], STDOUT_FILENO);
      xclose(fd[1]);
    }
  if (exec->fd[2] != -1)
    {
      xdup2(fd[2], STDERR_FILENO);
      xclose(fd[2]);
    }
  close_fd(exec->fd);
  return (i);
}

int		pipe_builtin(char **cmd, t_exec *exec, t_lpid *lpid, int i)
{
  pid_t		pid;

  pid = xfork();
  if (pid == -1)
    return (EXIT_FAILURE);
  if (pid)
    {
      close_fd(exec->fd);
      if (!exec->background && !lpid)
	add_job(pid, my_implode(cmd), exec);
      else if (!exec->background)
	update_pipe(lpid, my_implode(cmd));
      return (pid);
    }
  else
    {
      exec_child(NULL, cmd, exec, lpid);
      exit(gl_builtins[i].func(cmd));
    }
  return (EXIT_FAILURE);
}

int		builtin_find(char **cmd, t_exec *exec,
			     t_lpid *lpid, int *found)
{
  int		i;
  char		buffer[12];

  i = -1;
  while (gl_builtins[++i].name != NULL)
    if (!my_strcmp(cmd[0], gl_builtins[i].name))
      {
	*found = 1;
	if (exec->pipe)
	  return (pipe_builtin(cmd, exec, lpid, i));
	else
	  {
	    i = exec_builtin(cmd, exec, i);
	    add_local("?", int_to_str(i, buffer));
	    return (i);
	  }
      }
  return (-1);
}
