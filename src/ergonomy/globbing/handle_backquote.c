/*
** handle_backcote.c for 42sh in /home/shotgun/svn/42sh/current/src/ergonomy/globbing
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 15:27:42 2010 cerisier mickael
** Last update Sat May  1 18:14:27 2010 mickael cerisier
*/

#include <stdlib.h>
#include "parser.h"
#include "execution.h"
#include "globbing.h"
#include "gl_vars.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

extern t_global gl_global;

static t_list	*read_backquote(int fd, t_list *list)
{
  int		nb;
  char		*str;
  char		buffer[4096];
  t_list	*new;

  str = NULL;
  while ((nb = xread(fd, buffer, 4095)) && nb != -1)
    {
      buffer[nb] = '\0';
      if (str)
	str = my_strcat(FIRST_FREE, str, buffer, NULL);
      else
	str = my_strdup(buffer);
    }
  new = put_tab_in_list(my_explode_no_glob(str), list);
  free(str);
  return (new);
}

static t_list	*exec_backquote(char *str, t_list *list)
{
  int		pid;
  int		fd[2];
  t_list	*new;

  if (xpipe(fd) == -1)
    return (list);
  new = list;
  if (!(pid = xfork()))
    {
      xclose(fd[0]);
      xdup2(fd[1], STDOUT_FILENO);
      gl_global.normal_tty = 0;
      launch_cmd(str, WITHOUT_HIST);
      xclose(fd[1]);
      exit(EXIT_SUCCESS);
    }
  else
    {
      xclose(fd[1]);
      new = read_backquote(fd[0], list);
      xclose(fd[0]);
      xwaitpid(pid, &pid, 0);
    }
  free(str);
  return (new);
}

static void	handle_globbing_begin(char *begin, t_list *new,
				      t_list *list, int env)
{
  t_list	*mem;
  t_list	*memfree;

  mem = new;
  while (mem && mem->next != list)
    mem = mem->next;
  if (mem)
    mem->data = my_strcat(ALL_FREE, begin, mem->data, 0);
  else
    free(begin);
  while (new && new->next != mem)
    new = new->next;
  if (new && mem)
    {
      memfree = mem;
      mem = handle_star_list(mem->data, mem->next, env);
      free(memfree->data);
      free(memfree);
      new->next = mem;
    }
}

static void	handle_backquote_2(int *i, char *str, t_list **new, int env)
{
  t_list	*mem;

  if (i[0] != 0)
    *new = exec_backquote(my_strndup(&str[i[1]], i[0]), *new);
  else
    {
      mem = *new;
      *new = xmalloc(sizeof(**new));
      (*new)->next = mem;
      (*new)->data = my_strdup(&str[i[1] + 1]);
      return ;
    }
  if (*new)
    {
      (*new)->data = my_strcat(FIRST_FREE, (*new)->data,
			       &str[i[0] + i[1] + 1], 0);
      mem = *new;
      *new = handle_star_list((*new)->data, (*new)->next, env);
      free(mem->data);
      free(mem);
    }
}

t_list		*handle_backquote(char *str, t_list *list, int env)
{
  int		i[3];
  char		*begin;
  t_list	*new;
  t_list	*mem;

  new = list;
  i[2] = char_find(str, '`');
  begin = my_strndup(str, i[2]);
  i[1] = i[2] + 1;
  i[0] = char_find(&str[i[1]], '`');
  if (i[0] > 0 || (i[0] == 0 && (i[2] != 0 || str[i[1] + i[0] + 1] != '\0')))
    {
      handle_backquote_2(i, str, &new, env);
      handle_globbing_begin(begin, new, list, env);
      if (new && char_find(new->data, '`') != -1)
	{
	  mem = new;
	  new = handle_backquote(new->data, new->next, env);
	  free(mem->data);
	  free(mem);
	}
    }
  else
    free(begin);
  return (new);
}
