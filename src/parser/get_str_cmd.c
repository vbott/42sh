/*
** get_str_cmd.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Fri May 14 16:11:58 2010 cerisier mickael
** Last update Fri May 14 20:52:18 2010 mickael cerisier
*/

#include <stdlib.h>
#include "parser.h"
#include "lib_includes/strings.h"

static char		*search_str_type(int type)
{
  int			i;
  extern t_prioop	gl_prio[];

  i = 0;
  while (gl_prio[i].data != 0 && gl_prio[i].type != type)
    i++;
  if (gl_prio[i].data != 0)
    return (gl_prio[i].data);
  return (0);
}

static char		*get_str_cmd_left(char *cmd, t_tree *tree)
{
  if (tree->type == T_LPARENTH)
    {
      if (cmd)
	cmd = my_strcat(FIRST_FREE, cmd, " (", NULL);
      else
	cmd = my_strdup("(");
    }
  cmd = get_str_cmd(cmd, tree->left);
  if (tree->type == T_LPARENTH)
    cmd = my_strcat(FIRST_FREE, cmd, " )", NULL);
  return (cmd);
}

char			*get_str_cmd(char *cmd, t_tree *tree)
{
  char			*data;

  if (tree)
    {
      if (tree->left)
	cmd = get_str_cmd_left(cmd, tree);
      data = search_str_type(tree->type);
      if (cmd)
	{
	  if (!data)
	    cmd = my_strcat(FIRST_FREE, cmd, " ", tree->data, NULL);
	  else if (data[0] == '>' || data[0] == '<')
	    cmd = my_strcat(FIRST_FREE, cmd, " ", data, " ", tree->data, NULL);
	  else if (tree->type != T_LPARENTH)
	    cmd = my_strcat(FIRST_FREE, cmd, " ", data, NULL);
	}
      else if (!data)
	cmd = my_strdup(tree->data);
      if (tree->right)
      	cmd = get_str_cmd(cmd, tree->right);
    }
  return (cmd);
}
