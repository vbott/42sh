/*
** exec_child.c for 42sh in /home/snap/projects/42sh/current
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Sun May  2 10:43:10 2010 botton vivien
** Last update Sat May 22 19:43:16 2010 gianni castellani
*/

#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "jobs.h"
#include "execution.h"
#include "lib_includes/aff.h"
#include "lib_includes/xfunctions.h"
#include "termcaps.h"
#include "gl_vars.h"

void			dup_fd(int fd[3])
{
  if (fd[0] != -1)
    xdup2(fd[0], STDIN_FILENO);
  if (fd[1] != -1)
    xdup2(fd[1], STDOUT_FILENO);
  if (fd[2] != -1)
    xdup2(fd[2], STDERR_FILENO);
}

void			close_fd(int fd[3])
{
  int			mem;

  mem = fd[1];
  if (fd[0] != -1)
    {
      xclose(fd[0]);
      fd[0] = -1;
    }
  if (fd[1] != -1)
    {
      xclose(fd[1]);
      fd[1] = -1;
    }
  if (fd[2] != -1)
    {
      if (fd[2] != mem)
	xclose(fd[2]);
      fd[2] = -1;
    }
}

void			change_pgid(t_exec *exec, t_lpid *lpid)
{
  extern t_global	gl_global;

  if (!exec->pipe || !lpid)
    xsetpgid(0, 0);
  else if (gl_global.gl_jobs)
    xsetpgid(0, gl_global.gl_jobs->pgid);
  if ((!exec->pipe || (exec->pipe && !lpid)))
    xtcsetpgrp(0, getpid());
}

void			exec_child(char *cmd, char **args,
				   t_exec *exec, t_lpid *lpid)
{
  extern t_global	gl_global;

  if (!exec->background && gl_global.normal_tty)
    change_pgid(exec, lpid);
  if (exec->pipe && cmd && exec->pipe != exec->fd[0])
    xclose(exec->pipe);
  dup_fd(exec->fd);
  unhook_signal();
  if (cmd)
    xexecve(cmd, args, gl_global.gl_env);
}

int			error_msg(char *name, char *err, int value)
{
  my_puterror(name);
  my_puterror(err);
  return (value);
}
