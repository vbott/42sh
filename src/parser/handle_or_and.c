/*
** handle_or_and.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 15:18:57 2010 gianni castellani
** Last update Thu Apr  1 15:18:59 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"

int		handle_or(t_tree *tree, t_lpid **lpid, t_exec *exec)
{
  int		data;

  data = exec_tree(tree->left, lpid, exec);
  exec->pipe = 0;
  *lpid = NULL;
  exec->fd[0] = -1;
  exec->fd[0] = -1;
  exec->fd[0] = -1;
  if (data != EXIT_SUCCESS)
    data = exec_tree(tree->right, lpid, exec);
  else
    free_tree(tree->right);
  return (data);
}

int		handle_and(t_tree *tree, t_lpid **lpid, t_exec *exec)
{
  int		data;

  data = exec_tree(tree->left, lpid, exec);
  exec->pipe = 0;
  *lpid = NULL;
  exec->fd[0] = -1;
  exec->fd[0] = -1;
  exec->fd[0] = -1;
  if (data != EXIT_SUCCESS)
    {
      free_tree(tree->right);
      return (EXIT_FAILURE);
    }
  data = exec_tree(tree->right, lpid, exec);
  return (data);
}
