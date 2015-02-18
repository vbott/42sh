/*
** free_token_list.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Thu May  6 10:51:54 2010 cerisier mickael
** Last update Thu May  6 10:51:54 2010 cerisier mickael
*/

#include <stdlib.h>
#include "parser.h"

void		free_token_list(t_token *token)
{
  t_token	*mem;

  while (token)
    {
      mem = token;
      token = token->next;
      if (mem->free == 1)
	free(mem->data);
      free(mem);
    }
}
