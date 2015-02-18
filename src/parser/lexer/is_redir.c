/*
** is_redir.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed May 19 18:52:32 2010 cerisier mickael
** Last update Wed May 19 18:52:32 2010 cerisier mickael
*/

#include "parser.h"

int		is_redir(int type)
{
  if (type == T_LRED || type == T_DLRED)
    return (1);
  if (type == T_RRED || type == T_ANDRED)
    return (1);
  if (type == T_DRRED || type == T_ANDDRED)
    return (1);
  return (0);
}
