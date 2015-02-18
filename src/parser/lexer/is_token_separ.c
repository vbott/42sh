/*
** is_token_separ.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed May 19 19:04:49 2010 cerisier mickael
** Last update Wed May 19 19:04:49 2010 cerisier mickael
*/

#include "parser.h"

int		is_token_separ(int type)
{
  if (type == T_SEMICOLON || type == T_BACKGROUND)
    return (1);
  if (type == T_OR || type == T_AND)
    return (1);
  if (type == T_PIPE)
    return (1);
  return (0);
}
