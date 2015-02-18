/*
** part_completion.c for 42sh in /u/all/bereng_p/cu/rendu/SVN/42sh/current
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun May 23 16:03:17 2010 philippe berenguel
** Last update Sun May 23 23:09:49 2010 philippe berenguel
*/

#include <stdlib.h>
#include "parser.h"
#include "builtins.h"
#include "ergonomy.h"
#include "completion.h"
#include "termcaps.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

static char	**my_cpy(char **tab)
{
  int		p;
  int		s;
  char		**new;

  p = 0;
  new = xmalloc((len_tab(tab) + 1) * sizeof(*new));
  while (tab[p] != NULL)
    {
      s = my_strlen(tab[p]) - 1;
      if (tab[p][s] == '/')
	{
	  s--;
	  while (tab[p][s - 1] != '/')
	    s--;
	}
      else
	while (tab[p][s - 1] != '/')
	  s--;
      new[p] = my_strdup(&tab[p][s]);
      p++;
    }
  new[p] = NULL;
  return (new);
}

static int	get_length(char *buffer, size_t *curs)
{
  int		p;
  int		size;

  p = curs[0];
  while (p > 0 && (buffer[p] == ' ' || buffer[p] == '\t'))
    p--;
  while (p > 0 && buffer[p] != ' ' && buffer[p] != '\t')
    p--;
  if (p > 0)
    p++;
  size = curs[0] - p;
  return (size);
}

void		part_completion(char **tab, char *buffer, size_t *curs,
				t_info *info)
{
  t_part	p;

  p.new_tab = (info->mode > 2 && tab && tab[0]) ? my_cpy(tab) : tab;
  p.s = get_length(buffer, curs);
  p.c = p.s;
  p.i = 0;
  while (p.i == 0)
    {
      p.i = 1;
      p.t = 0;
      while (p.new_tab && p.new_tab[p.t] && p.new_tab[p.t + 1] &&
	     p.new_tab[p.t][p.c] && p.new_tab[p.t + 1][p.c] &&
	     p.new_tab[p.t][p.c] == p.new_tab[p.t + 1][p.c])
	p.t += 1;
      if (p.new_tab && p.new_tab[p.t + 1] == NULL)
	{
	  p.i = 0;
	  p.t = 0;
	  p.c += 1;
	}
   }
  if (p.t)
    choose_printing(&p, info, buffer, curs);
}
