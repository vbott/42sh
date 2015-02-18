/*
** free_tree.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon May 17 17:57:03 2010 cerisier mickael
** Last update Mon May 17 17:57:03 2010 cerisier mickael
*/

#include <stdlib.h>
#include "parser.h"

void		free_tree(t_tree *tree)
{
  if (tree)
    {
      if (tree->free)
	free(tree->data);
      if (tree->left)
	free_tree(tree->left);
      if (tree->right)
	free_tree(tree->right);
      free(tree);
    }
}
