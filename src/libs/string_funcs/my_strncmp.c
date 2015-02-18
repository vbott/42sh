/*
** my_strncmp.c for 42sh in /u/epitech_2014/bereng_p/public/42group/test_backup/parser
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun Mar 14 13:30:22 2010 gianni castellani
** Last update Sun Mar 14 13:33:56 2010 gianni castellani
*/

#include <stdlib.h>

int		my_strncmp(char *str, char *str2, int len)
{
  int		cpt;

  cpt = 0;
  if (str2 == NULL)
    return (0);
  while (cpt < len && str[cpt] != '\0' && str2[cpt] != '\0')
    {
      if (str[cpt] != str2[cpt])
	return (0);
      cpt++;
    }
  if (cpt < len)
    return (0);
  return (1);
}
