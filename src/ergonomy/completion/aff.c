/*
** aff.c for 42sh in /home/snap/projects/42sh/current
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Thu May  6 11:21:51 2010 botton vivien
** Last update Sun May 23 23:16:08 2010 philippe berenguel
*/

#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "builtins.h"
#include "ergonomy.h"
#include "completion.h"
#include "termcaps.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

static void	clean_aff(char *tab)
{
  int		p;

  p = my_strlen(tab);
  if (tab[p - 1] == '/')
    {
      while (p > 0 && tab[p] != '/')
	p--;
      if (p != 0)
	p--;
      while (p > 0 && tab[p] != '/')
	p--;
      if (tab[p] == '/')
	p++;
      else if (p > 0 && tab[p] != '.')
	p += 2;
    }
  else
    {
      while (p > 0 && tab[p] != '/')
	p--;
      p++;
    }
  my_putstr(&tab[p]);
}

static void	case_two(char **tab, char *buffer, size_t *curs,
			 t_info *info)
{
  int		p;

  part_completion(tab, buffer, curs, info);
  p = 0;
  my_putchar('\n');
  if (info->to_match && (my_strncmp(info->to_match, "cd", 2) == 1))
    cd_case(tab);
  else if (info->to_match && (my_strncmp(info->to_match, "~/", 2) == 1))
    tilde_case_two(tab, buffer, curs);
  else
    while (tab && tab[p])
      {
	clean_aff(tab[p]);
	my_putchar('\n');
	p++;
      }
  aff_prompt();
  xwrite(STDOUT_FILENO, buffer, curs[1]);
  begin_cursor(curs);
}

static void	case_one(int s, int *c, char **tab, char *buffer)
{
  int		p;
  int		n;
  int		t;

  p = 0;
  n = 0;
  t = 0;
  while (*c >= 0 && buffer[*c] != ' ' && buffer[*c] != '\t')
    {
      if (buffer[*c] == '/')
	n++;
      (*c)--;
    }
  if (buffer[*c + 1] == '~' && buffer[*c + 2] == '/')
    tilde_case(&p, &n, &t, tab);
  else if (buffer[*c + 1] == '.' && buffer[*c + 2] == '/')
    {
      n = 0;
      *c = *c + 1;
    }
  else
    n = (n >= 1) ? -1 : 1;
  *c = s - *c + n + t;
}

static void	unique_printing_calc(char **tab, char *buffer, int *s, int *c)
{
  if (buffer[*c] == '.' && buffer[*c + 1] == '/')
    (*c) += 2;
  while (buffer && buffer[*c] && tab[0][*s] && buffer[*c] == tab[0][*s])
    {
      (*c)++;
      (*s)++;
    }
}

void		aff(char **tab, char *buffer, size_t *curs, t_info *info)
{
  int		s;
  int		c;

  s = 0;
  if (tab && len_tab(tab) == 1)
    {
      c = curs[0];
      if (((buffer[c] == ' ' || buffer[c] == '\t') &&
	   no_hidden_files(buffer, &c, &s) == 1) ||
	  hidden_files(buffer, &c, &s, curs) == 1)
	{
	  unique_printing_calc(tab, buffer, &s, &c);
	  add_char(buffer, &tab[0][s], curs);
	}
      else if (buffer[c] != ' ' && buffer[c] != '\t')
	{
	  case_one(c, &c, tab, buffer);
	  while (buffer && buffer[c] && tab[0][c] && buffer[c] == tab[0][c])
	    c++;
	  add_char(buffer, &tab[0][c], curs);
	}
    }
  else if (tab && len_tab(tab) > 0)
    case_two(tab, buffer, curs, info);
}
