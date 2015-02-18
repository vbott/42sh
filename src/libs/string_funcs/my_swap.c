/*
** my_swap.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:38:58 2010 cerisier mickael
** Last update Wed Apr 28 11:38:58 2010 cerisier mickael
*/

void		my_swap(int **a, int **b)
{
  int		*mem;

  mem = *a;
  *a = *b;
  *b = mem;
}
