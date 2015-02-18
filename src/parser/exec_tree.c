/*
** exec_tree.c for plop in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Apr 26 14:13:46 2010 cerisier mickael
** Last update Sat May  1 16:11:14 2010 mickael cerisier
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parser.h"
#include "execution.h"
#include "lib_includes/free.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

t_vfunc			gl_parserfunc[] = {
  {T_SEMICOLON, handle_semicolon},
  {T_PIPE, handle_pipe},
  {T_RRED, handle_redir_right},
  {T_DRRED, handle_redir_right},
  {T_ANDRED, handle_redir_error},
  {T_ANDDRED, handle_redir_error},
  {T_LRED, handle_redir_left},
  {T_DLRED, handle_redir_left},
  {T_COMMAND, exec_command},
  {T_AND, handle_and},
  {T_OR, handle_or},
  {T_BACKGROUND, handle_background},
  {T_LPARENTH, handle_parenthesis},
  {0, 0}
};

t_lpid		*add_pid(int pid, t_lpid *lpid)
{
  t_lpid	*new;

  new = xmalloc(sizeof(*new));
  new->pid = pid;
  new->done = 0;
  new->next = lpid;
  return (new);
}

static  int	exec_cmd(char *str, t_lpid **lpid, t_exec *exec)
{
  int		data;
  char		**tab;
  char		**tabstar;

  tab = my_explode(str, ' ');
  if (tab == NULL)
    return (EXIT_FAILURE);
  if (my_strcmp(tab[0], "unsetenv") && my_strcmp(tab[0], "setenv"))
    {
      tabstar = handle_star(tab, WITHOUT_ENV);
      free(tab);
      data = cmd_find(tabstar, exec, *lpid);
      free_tab(tabstar);
    }
  else
    {
      data = cmd_find(tab, exec, *lpid);
      free(tab);
    }
  return (data);
}

int		exec_command(t_tree *tree, t_lpid **lpid, t_exec *exec)
{
  int		data;
  int		mem;
  char		*memfree;

  memfree = tree->data;
  mem = handle_dollar(&(tree->data));
  data = exec_cmd(tree->data, lpid, exec);
  if (tree->free)
    free(memfree);
  if (mem == 1)
    free(tree->data);
  if (exec->pipe && data > 0)
    *lpid = add_pid(data, *lpid);
  return (data);
}

int		exec_tree(t_tree *tree, t_lpid **lpid, t_exec *exec)
{
  int		i;
  int		data;

  if (tree == NULL)
    return (EXIT_FAILURE);
  data = EXIT_FAILURE;
  i = 0;
  while (gl_parserfunc[i].data != 0 && gl_parserfunc[i].data != tree->type)
    i++;
  if (gl_parserfunc[i].data != 0)
    {
      data = gl_parserfunc[i].func(tree, lpid, exec);
      free(tree);
    }
  else
    free_tree(tree);
  return (data);
}
