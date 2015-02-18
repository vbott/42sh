/*
** handle_parenthesis.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Fri May 14 16:00:44 2010 cerisier mickael
** Last update Fri May 21 17:42:56 2010 vivien botton
*/

#include <stdlib.h>
#include "parser.h"
#include "jobs.h"
#include "execution.h"
#include "gl_vars.h"
#include "lib_includes/xfunctions.h"

static void		handle_child_parenth(t_tree *tree, t_exec *exec,
					     t_lpid *lpid)
{
  t_lpid		*newlpid;
  extern t_global	gl_global;

  if (!exec->background && gl_global.normal_tty)
    change_pgid(exec, lpid);
  if (exec->pipe && exec->pipe != exec->fd[0])
    xclose(exec->pipe);
  unhook_signal();
  dup_fd(exec->fd);
  exec->pipe = 0;
  exec->parenthesis = 1;
  exec->background = -1;
  newlpid = NULL;
  exit(exec_tree(tree->left, &newlpid, exec));
}

static void		jobs_in_parenthesis(int pid, t_tree *tree,
				    t_lpid **lpid, t_exec *exec)
{
  char			*cmd;

  cmd = get_str_cmd(NULL, tree->left);
  free_tree(tree->left);
  if (*lpid)
    update_pipe(*lpid, cmd);
  else
    add_job(pid, cmd, exec);
  *lpid = add_pid(pid, *lpid);
}

static int		free_with_return(t_tree *tree)
{
  free_tree(tree->left);
  free_tree(tree->right);
  return (EXIT_FAILURE);
}

int			handle_parenthesis(t_tree *tree, t_lpid **lpid,
					   t_exec *exec)
{
  int			pid;
  int			status;

  pid = xfork();
  if (pid == -1)
    free_with_return(tree);
  if (pid)
    {
      close_fd(exec->fd);
      if (exec->pipe)
	{
	  jobs_in_parenthesis(pid, tree, lpid, exec);
	  return (pid);
	}
      else
	add_job(pid, get_str_cmd(NULL, tree->left), exec);
      free_tree(tree->left);
      if (handle_status(pid, &status, 1, exec->background) != EXIT_SUCCESS)
	return (EXIT_FAILURE);
      return (status);
    }
  else
    handle_child_parenth(tree, exec, *lpid);
  return (EXIT_SUCCESS);
}
