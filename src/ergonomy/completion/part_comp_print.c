/*
** part_comp_print.c for 42sh in /u/all/bereng_p/cu/rendu/SVN/42sh/current/src/ergonomy/completion
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun May 23 23:15:26 2010 philippe berenguel
** Last update Sun May 23 23:19:02 2010 philippe berenguel
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

static void	printing(t_part *p, t_info *info, char *buffer, size_t *curs)
{
  char		*part;
  int		f;

  f = 0;
  p->i = p->s;
  p->s = p->c - p->s;
  if (info->mode == 2 && buffer[curs[0] - p->s] != '.')
    {
      p->t = p->i + 2;
      p->s -= 2;
    }
  else
    p->t = p->i;
  if (p->s > 0)
    {
      part = my_strndup(&(p->new_tab[0][p->t]), p->s);
      add_char(buffer, part, curs);
      free(part);
    }
  if (info->mode > 2 && p->new_tab)
    {
      while (p->new_tab[f])
	free(p->new_tab[f++]);
      free(p->new_tab);
    }
}

static void	printing_tilde(t_part *p, int pos, char *buffer,
			       size_t *curs)
{
  char		*part;

  part = my_strndup(&(p->new_tab[0][pos]), (p->t - pos));
  add_char(buffer, part, curs);
  free(part);
}

void		choose_printing(t_part *p, t_info *info, char *buffer,
				size_t *curs)
{
  int		pos;
  unsigned int	c;
  int		s;

  c = curs[0];
  s = -1;
  if (info->to_match && 
      info->to_match[0] == '~' && info->to_match[1] == '/')
    {
      if (c == curs[1])
	c--;
      while (c > 0 && buffer[c] != ' ' && buffer[c] != '\t')
	c--;
      if (buffer[c] == ' ' || buffer[c] == '\t')
	c++;
      pos = c;
      while (buffer[c] && buffer[c] != ' ' && buffer[c] != '\t' && s < 4)
	if (buffer[++c] == '/')
	  s++;
      pos = c - pos + 1;
      printing_tilde(p, pos, buffer, curs);
    }
  else
    printing(p, info, buffer, curs);
}
