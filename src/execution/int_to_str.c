/*
** int_to_str.c for corewar in /u/all/botton_v/cu/projects/corewar/vm
** 
** Made by vivien botton
** Login   <botton_v@epitech.net>
** 
** Started on  Mon Mar 29 07:52:09 2010 vivien botton
** Last update Mon Mar 29 07:52:10 2010 vivien botton
*/

int		calc_len_int(int nb)
{
  int		res;
  int		i;

  res = 0;
  i = 1;
  while (nb > 0)
    {
      res++;
      nb /= 10;
      i++;
    }
  return (res);
}

char		*int_to_str(int nb, char *str)
{
  int		len;

  len = calc_len_int(nb);
  if (nb == 0)
    {
      str[0] = '0';
      str[1] = '\0';
      return (str);
    }
  str[len] = '\0';
  len--;
  while (len >= 0)
    {
      str[len] = nb % 10 + '0';
      nb = nb / 10;
      len--;
    }
  return (str);
}
