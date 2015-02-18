/*
** my_strcpy.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat May  8 18:18:43 2010 gianni castellani
** Last update Mon May 10 15:12:27 2010 gianni castellani
*/

void		my_strcpy(char *str, char *str2)
{
  int		cpt;

  cpt = 0;
  while (str2[cpt] != '\0')
    {
      str[cpt] = str2[cpt];
      cpt++;
    }
}
