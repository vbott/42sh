/*
** handle_redir_error.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon May 17 20:01:03 2010 cerisier mickael
** Last update Mon May 17 20:01:03 2010 cerisier mickael
*/

#include <stdlib.h>
#include "parser.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"

int		handle_redir_error(t_tree *tree, t_lpid **lpid, t_exec *exec)
{
  int		fd;

  if (tree->type == T_ANDRED)
    fd = O_CREAT | O_TRUNC | O_WRONLY;
  else
    fd = O_CREAT | O_APPEND | O_WRONLY;
  if ((fd = xopen(tree->data, fd, MODE_OPEN)) == -1)
    {
      free(tree->data);
      return (EXIT_FAILURE);
    }
  free(tree->data);
  exec->fd[1] = fd;
  exec->fd[2] = fd;
  return (exec_tree(tree->left, lpid, exec));
}
