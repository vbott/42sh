/*
** aff_cases.c for 42sh in /u/all/bereng_p/cu/rendu/SVN/42sh/current
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun May 23 16:02:55 2010 philippe berenguel
** Last update Sun May 23 23:23:48 2010 carole cailleux
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

void		cd_case(char **tab)
{
  int		p;

  p = 0;
  while (tab && tab[p])
    {
      if (tab[p][my_strlen(tab[p])] == '/')
	{
	  my_putstr(tab[p]);
	  my_putchar('\n');
	}
      p++;
    }
}

void		tilde_case(int *p, int *n, int *t, char **tab)
{
  while (*p < 2 && tab[0][*t])
    if (tab[0][(*t)++] == '/')
      (*p)++;
  if (*n >= 1)
    *n = 2;
}

void		tilde_case_two(char **tab, char *buffer, size_t *curs)
{
  int		p;
  unsigned int	c;
  int		s;

  c = curs[0];
  s = -1;
  if (c == curs[1])
    c--;
  while (c > 0 && buffer[c] != ' ' && buffer[c] != '\t')
    c--;
  if (buffer[c] == ' ' || buffer[c] == '\t')
    c++;
  p = c;
  while (buffer[c] && buffer[c] != ' ' && buffer[c] != '\t' && s < 4)
    if (buffer[++c] == '/')
      s++;
  p = c - p + 1;
  s = 0;
  while (tab[s])
    {
      my_putstr(&tab[s++][p]);
      my_putchar('\n');
    }
}

int		hidden_files(char *buffer, int *c, int *s, size_t *curs)
{
  int		p;

  p = *c;
  while (*c > 0 && buffer[*c] != '.')
    (*c)--;
  if (buffer[*c + 1] != '/' && (*c > 0 || buffer[*c] == '.'))
    {
      if (*c == 0 && buffer[*c] != '.')
	*s = 2;
      else
	*s = 0;
      if (buffer[p] == ' ' || buffer[p] == '\t')
	p--;
      while (p > 0 && buffer[p] != ' ' && buffer[p] != '\t')
	p--;
      if (buffer[p] == ' ' || buffer[p] == '\t')
	p++;
      *c = p;
      return (1);
    }
  else
    {
      *c = curs[0];
      return (0);
    }
}

int		no_hidden_files(char *buffer, int *c, int *s)
{
  if (*c > 0 && (buffer[*c] == ' ' || buffer[*c] == '\t'))
    (*c)--;
  while (*c > 0 && buffer[*c] != ' ' && buffer[*c] != '\t')
    (*c)--;
  if (buffer[*c] == ' ' || buffer[*c] == '\t')
    {
      (*c)++;
      (*s) += 2;
    }
  return (1);
}
