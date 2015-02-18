/*
** replace_redirerr.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun May 23 14:32:02 2010 gianni castellani
** Last update Sun May 23 15:45:50 2010 gianni castellani
*/

#include "parser.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"

int			new_type(int type)
{
  if (type == T_RRED)
    return (T_ANDRED);
  return (T_ANDDRED);
}

int			is_rredir(int type)
{
  if (type == T_RRED || type == T_DRRED)
    return (1);
  return (0);
}

void			new_command_name(t_token *tok)
{
  int			cpt;
  char			*tmp;

  cpt = 0;
  while (tok->data[cpt] && tok->data[cpt] != ' ')
    cpt++;
  if (!tok->data[cpt])
    return ;
  while (tok->data[cpt] == ' ')
    cpt++;
  tmp = my_strdup(tok->data + cpt);
  if (tok->free)
    free(tok->data);
  tok->free = 1;
  tok->data = tmp;
}

void			modif_list(t_token *cur)
{
  t_token		*temp;

  cur->type = new_type(cur->type);
  if (cur->next->next && cur->next->next->type == T_COMMAND)
    {
      cur->data = my_strcdup(cur->next->next->data, ' ');
      cur->free = 1;
      if (!my_strcmp(cur->data, cur->next->next->data))
	{
	  temp = cur->next->next->next;
	  free(cur->next->next);
	}
      else
	{
	  temp = cur->next->next;
	  new_command_name(cur->next->next);
	}
    }
  else
    temp = cur->next->next;
  free(cur->next);
  cur->next = temp;
}

int			replace_redirerr(t_token *token)
{
  t_token		*cur;

  cur = token;
  while (cur)
    {
      if (is_rredir(cur->type) && !cur->data && cur->next
	  && cur->next->type == T_BACKGROUND)
	modif_list(cur);
      cur = cur->next;
    }
  return (1);
}
