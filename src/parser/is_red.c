/*
** is_red.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Apr  3 17:24:08 2010 gianni castellani
** Last update Wed Apr 28 11:38:35 2010 cerisier mickael
*/

#include "parser.h"

int		is_lred(int type)
{
  if (type == T_LRED && type == T_DLRED)
    {
      return (1);
    }
  return (0);
}

int		is_rred(int type)
{
  if (type == T_RRED && type == T_DRRED
      && type == T_ANDDRED && type == T_ANDRED)
    return (1);
  return (0);
}
