/*
** match.c for my_ls in /u/all/castel_a/cu/rendu/c/my_ls
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Tue Dec  8 14:38:30 2009 gianni castellani
** Last update Sat May  1 15:13:28 2010 mickael cerisier
*/

#include "globbing.h"

static int	handle_backet(char c, char *str)
{
  int		i;
  int		mem;

  i = 1;
  mem = 0;
  while (str[i] != '\0' && str[i] != ']')
    {
      if (c == str[i])
	mem = 1;
      i++;
    }
  if (mem)
    return (i);
  return (-1);
}

static int	match_globbing(char *str, char*str2, int *cpt, int *cpt2)
{
  int		mem;

  if (str2[*cpt2] == '[')
    {
      mem = *cpt2;
      *cpt2 += handle_backet(str[*cpt], &str2[*cpt2]);
      if (mem > *cpt2)
	return (0);
    }
  else if (str2[*cpt2] == '*')
    {
      mem = 0;
      while (str2[*cpt2] == '*')
	(*cpt2)++;
      (*cpt2)--;
      while (str[*cpt] != '\0' &&
	     (mem = match(&str[*cpt], &str2[*cpt2 + 1])) <= 0)
	(*cpt)++;
      if (mem)
	return (1);
    }
  else if (str[*cpt] == '\0')
    return (0);
  return (-1);
}

static int	match_quote(char *str, char *str2, int *cpt, int *cpt2)
{
  char		c;

  c = str2[*cpt2];
  (*cpt2)++;
  while (str2[*cpt2] != '\0' && str2[*cpt2] != c)
    {
      if (str[*cpt] != str2[*cpt2])
	return (0);
      (*cpt2)++;
      (*cpt)++;
    }
  (*cpt)--;
  return (1);
}

int		match(char *str, char *str2)
{
  int		cpt;
  int		cpt2;
  int		mem;

  cpt = 0;
  cpt2 = 0;
  while (str2[cpt2] != '\0')
    {
      mem = 0;
      if ((str2[cpt2] == '"' || str2[cpt2] == '\'')
	  && !(mem = match_quote(str, str2, &cpt, &cpt2)))
	return (0);
      if (!mem && str2[cpt2] != '[' && str2[cpt2] != '*'
	  && str2[cpt2] != '?' && str[cpt] != str2[cpt2])
	return (0);
      if ((mem = match_globbing(str, str2, &cpt, &cpt2)) != -1)
	return (mem);
      cpt2 += (str2[cpt2] != '\0') ? 1 : 0;
      cpt += (str[cpt] != '\0') ? 1 : 0;
    }
  if (str[cpt] != '\0')
    return (0);
  return (1);
}
