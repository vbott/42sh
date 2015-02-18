/*
** handle_background.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Sat May  8 18:05:58 2010 cerisier mickael
** Last update Sat May 22 17:44:58 2010 vivien botton
*/

#include <stdlib.h>
#include "parser.h"
#include "jobs.h"
#include "execution.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/strings.h"

int			error_backround(t_tree *tree)
{
  free_tree(tree->left);
  free_tree(tree->right);
  return (EXIT_FAILURE);
}

int			handle_background(t_tree *tree, t_lpid **lpid,
					  t_exec *exec)
{
  int			pid;

  pid = xfork();
  if (pid == -1)
    return (error_backround(tree));
  exec->background = 1;
  if (pid)
    {
      add_job(pid, get_str_cmd(NULL, tree->left), exec);
      exec->background = 0;
      free_tree(tree->left);
      pid = (tree->right) ? exec_tree(tree->right, lpid, exec) : EXIT_SUCCESS;
      return (pid);
    }
  else
    {
      *lpid = NULL;
      xsetpgid(0, 0);
      unhook_signal();
      pid = exec_tree(tree->left, lpid, exec);
      pid = (pid == EXIT_FAILURE) ? 256 : pid;
      exit(pid);
    }
  return (EXIT_FAILURE);
}
