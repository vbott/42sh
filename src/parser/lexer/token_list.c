/*
** token_list.c for 42sh in /u/all/castel_a/cu/42sh/current/src/parser
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat May  1 11:44:51 2010 gianni castellani
** Last update Sun May 23 14:10:50 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"
#include "lib_includes/strings.h"
#include "lib_includes/aff.h"
#include "lib_includes/xfunctions.h"

extern t_prioop		gl_prio[];

t_prioop		*search_token(char *str, int cpt)
{
  int			cpt2;

  cpt2 = 0;
  while (gl_prio[cpt2].type != 0 &&
	 !my_strncmp(str + cpt, gl_prio[cpt2].data, gl_prio[cpt2].len))
    cpt2++;
  if (gl_prio[cpt2].type)
    return (&gl_prio[cpt2]);
  return (NULL);
}

char			*find_filename(char *str, t_prioop *prio)
{
  int			cpt;
  char			*ret;
  int			len;

  cpt = 0;
  while (cpt < prio->len)
    str[cpt++] = ' ';
  while (str[cpt] == ' ' || str[cpt] == '\t')
    cpt++;
  if (str[cpt] == '\0' || search_token(str, cpt))
    return (NULL);
  len = cpt;
  while (str[len] != '\0' && str[len] != ' '
	 && str[len] != '\t' && !search_token(str, len))
    len++;
  ret = my_strndup(str + cpt, len - cpt);
  while (str[cpt] != ' '  && str[cpt] != '\t'
	 && str[cpt] != '\0' && !search_token(str, cpt))
    str[cpt++] = ' ';
  return (ret);
}

t_token			*create_token(char *str, t_prioop *prio)
{
  t_token		*token;

  token = xmalloc(sizeof(*token));
  token->type = prio->type;
  if (is_redir(prio->type))
    {
      token->free = 1;
      token->data = find_filename(str, prio);
    }
  else
    {
      token->free = 0;
      token->data = NULL;
    }
  str[0] = '\0';
  return (token);
}

t_token			*create_cmd_token(char *str, int *cpt)
{
  t_token		*token;
  int			c;
  int			cpt2;

  cpt2 = 0;
  c = 0;
  while (str[*cpt] != '\0' && (c || !search_token(str, *cpt)))
    {
      if (str[*cpt] != ' ' && str[*cpt] != '\t')
	cpt2 = *cpt;
      if (str[*cpt] == '\\')
	(*cpt)++;
      else if (!c && (str[*cpt] == '"' || str[*cpt] == '\''
		      || str[*cpt] == '`'))
	c = str[*cpt];
      else if (c == str[*cpt])
	c = 0;
      (str[*cpt] != '\0') ? ((*cpt)++) : ((*cpt));
    }
  if (str[cpt2] != '\0' && (str[cpt2 + 1] == ' ' || str[cpt2 + 1] == '\t'))
    str[cpt2 + 1] = '\0';
  token = xmalloc(sizeof(*token));
  token->type = T_COMMAND;
  token->data = str;
  return (token);
}

t_token			*create_token_list(char *str)
{
  int			cpt;
  t_token		*token;
  t_prioop		*prio;

  token = NULL;
  while (str[0] == ' ' || str[0] == '\t')
    {
      str[0] = '\0';
      str++;
    }
  if (str[0] != '\0' && (prio = search_token(str, 0)))
    {
      token = create_token(str, prio);
      token->next = create_token_list(str + prio->len);
    }
  else if (str[0] != '\0')
    {
      cpt = 0;
      token = create_cmd_token(str, &cpt);
      token->free = 0;
      token->next = create_token_list(str + cpt);
    }
  return (token);
}
