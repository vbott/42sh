/*
** my_putnbr.c for 42sh in /u/all/bereng_p/cu/public/42group/current/headers/lib_headers
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 11:13:44 2010 philippe berenguel
** Last update Sun Mar 14 11:14:36 2010 philippe berenguel
*/

#include "lib_includes/aff.h"

void		my_putnbr(int nb)
{
  if (nb < 0)
    {
      nb *= -1;
      my_putchar('-');
    }
  if (nb / 10 > 0)
    my_putnbr(nb / 10);
  my_putchar((nb % 10) + '0');
}
