/*
** handlers.c for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh/parser
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 13:40:22 2010 philippe berenguel
** Last update Fri May 21 17:08:18 2010 vivien botton
*/

#include <stdlib.h>
#include <sys/wait.h>
#include "parser.h"
#include "execution.h"
#include "jobs.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"

int		handle_wait_pipe(t_lpid *lpid, int bg)
{
  int		status;
  t_lpid	*cpy;

  cpy = lpid;
  status = EXIT_FAILURE;
  while (cpy)
    {
      if (!cpy->done && !handle_status(cpy->pid, &status, 0, bg)
	  && !WIFSTOPPED(status))
	cpy->done = 1;
      cpy = cpy->next;
    }
  if (!bg)
    xtcsetpgrp(STDIN_FILENO, getpid());
  del_job(lpid, bg);
  return (status);
}

static t_lpid	*rev_lpid(t_lpid *list, t_lpid *next)
{
  t_lpid	*mem;

  mem = list;
  list = list->next;
  mem->next = next;
  if (list)
    return (rev_lpid(list, mem));
  return (mem);
}

int		handle_pipe(t_tree *tree, t_lpid **lpid, t_exec *exec)
{
  int		data;
  int		dowait;
  int		fd[2];

  if (!(*lpid))
    dowait = 1;
  else
    dowait = 0;
  if (xpipe(fd) == -1)
    return (EXIT_FAILURE);
  exec->pipe = fd[0];
  exec->fd[1] = fd[1];
  data = exec_tree(tree->left, lpid, exec);
  if (*lpid)
    {
      exec->fd[0] = fd[0];
      exec_tree(tree->right, lpid, exec);
      if (dowait)
	{
	  *lpid = rev_lpid(*lpid, 0);
	  return (handle_wait_pipe(*lpid, exec->background));
	}
      return (EXIT_FAILURE);
    }
  return (EXIT_FAILURE);
}

int		handle_semicolon(t_tree *tree, t_lpid **lpid, t_exec *exec)
{
  exec_tree(tree->left, lpid, exec);
  exec->pipe = 0;
  *lpid = NULL;
  exec->fd[0] = -1;
  exec->fd[1] = -1;
  exec->fd[2] = -1;
  return (exec_tree(tree->right, lpid, exec));
}
