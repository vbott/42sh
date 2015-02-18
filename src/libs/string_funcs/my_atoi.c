/*
** my_atoi.c for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh/libs/string_funcs
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 13:35:13 2010 philippe berenguel
** Last update Fri Apr  2 13:35:13 2010 philippe berenguel
*/

int		my_atoi(const char *str)
{
  int		res;

  if (*str == '-')
    return (-my_atoi(str + 1));
  if (*str == '+' || *str == ' ' || *str == '\t')
    return (my_atoi(str + 1));
  res = 0;
  while (*str >= '0' && *str <= '9')
    {
      res = res * 10;
      res = res + *str - '0';
      str = str + 1;
    }
  return (res);
}
