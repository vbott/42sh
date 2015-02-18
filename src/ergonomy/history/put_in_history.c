/*
** put_in_historic.c for 42sh in /u/all/castel_a/cu/42sh/current/src/ergonomy/history
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun Apr 18 10:53:45 2010 gianni castellani
** Last update Sun May 23 17:03:48 2010 gianni castellani
*/

#include <unistd.h>
#include <stdlib.h>
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"

extern t_prioop		gl_prio[];

t_prioop		search_prio(int type)
{
  int			cpt;

  cpt = 0;
  while (gl_prio[cpt].type && gl_prio[cpt].type != type)
    cpt++;
  return (gl_prio[cpt]);
}

int			name_len(t_token *token)
{
  int			len;
  t_prioop		prio;

  len = 0;
  while (token != NULL)
    {
      prio = search_prio(token->type);
      if (prio.type)
	len += prio.len;
      if (token->data)
	{
	  if (len != 0 && token->type != T_COMMAND)
	    len++;
	  len += my_strlen(token->data);
	}
      if (token->next)
	len++;
      token = token->next;
    }
  return (len);
}

void			put_data(t_token *token, char *ret, int *cpt)
{
  if (token->data)
    {
      if (*cpt != 0 && token->type != T_COMMAND)
	my_strcpy(ret + (*cpt)++, " ");
      my_strcpy(ret + *cpt, token->data);
      *cpt += my_strlen(token->data);
    }
}

char			*find_name(t_token *token)
{
  char			*ret;
  int			len;
  int			cpt;
  t_prioop		prio;

  len = name_len(token);
  ret = xmalloc((len + 1) * sizeof(*ret));
  cpt = 0;
  while (token != NULL)
    {
      prio = search_prio(token->type);
      if (prio.type)
	{
	  my_strcpy(ret + cpt, prio.data);
	  cpt += prio.len;
	}
      put_data(token, ret, &cpt);
      if (token->next)
	my_strcpy(ret + cpt++, " ");
      token = token->next;
    }
  ret[cpt] = '\0';
  return (ret);
}

void			put_in_history(t_token *token)
{
  extern t_global	gl_global;
  char			*str;
  t_history		*hist;

  str = find_name(token);
  if (!gl_global.history || my_strcmp(str, gl_global.history->data))
    {
      while (gl_global.hist_len >= get_histsize())
	delete_first_node();
      gl_global.hist_len++;
      hist = xmalloc(sizeof(*hist));
      hist->data = str;
      hist->next = gl_global.history;
      hist->prev = NULL;
      if (gl_global.history)
	gl_global.history->prev = hist;
      else
	gl_global.begin_hist = hist;
      gl_global.history = hist;
    }
  else
    free(str);
}
