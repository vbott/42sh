/*
** handle_redir.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:56:08 2010 cerisier mickael
** Last update Sun May  2 15:54:52 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"

int		handle_redir_right(t_tree *tree, t_lpid **lpid, t_exec *exec)
{
  int		fd;

  if (tree->type == T_RRED)
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
  return (exec_tree(tree->left, lpid, exec));
}

static void	handle_dredir_left(char *str, int fd)
{
  int		i;
  char		buffer[4096];

  my_putstr("? ");
  while ((i = xread(STDIN_FILENO, buffer, 4095)) && i != -1)
    {
      buffer[i] = '\0';
      if (my_strccmp(str, buffer, '\n'))
	return ;
      xwrite(fd, buffer, i);
      my_putstr("? ");
    }
}

int		handle_redir_left(t_tree *tree, t_lpid **lpid, t_exec *exec)
{
  int		fd[2];

  if (tree->type == T_LRED)
    {
      if ((fd[0] = xopen(tree->data, O_RDONLY, 0)) == -1)
	{
	  free(tree->data);
	  free_tree(tree->right);
	  return (EXIT_FAILURE);
	}
    }
  else
    {
      if (xpipe(fd) == -1)
	{
	  free(tree->data);
	  free_tree(tree->right);
	  return (EXIT_FAILURE);
	}
      handle_dredir_left(tree->data, fd[1]);
      xclose(fd[1]);
    }
  free(tree->data);
  exec->fd[0] = fd[0];
  return (exec_tree(tree->right, lpid, exec));
}
