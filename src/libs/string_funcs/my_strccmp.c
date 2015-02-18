/*
** my_strccmp.c for 42sh in /u/epitech_2014/bereng_p/public/42group/test_backup/libs/string_funcs
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Mar 13 18:50:21 2010 gianni castellani
** Last update Sun Mar 14 11:12:21 2010 philippe berenguel
*/

int		my_strccmp(const char *s1, const char *s2, char c)
{
  int		cpt;
  int		res;

  res = 0;
  cpt = 0;
  while (s1[cpt] != '\0' && s2[cpt] != '\0' && s1[cpt] != c && s2[cpt] != c)
    {
      if (s1[cpt] != s2[cpt])
	return (0);
      cpt++;
    }
  if ((s1[cpt] == '\0' || s1[cpt] == c) && (s2[cpt] == '\0' || s2[cpt] == c))
    return (1);
  return (0);
}
