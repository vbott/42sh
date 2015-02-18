/*
** ergonomy.h for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh/headers
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 13:52:30 2010 philippe berenguel
** Last update Wed May  5 21:17:10 2010 philippe berenguel
*/

#ifndef		_ERGONOMY_H_
# define	_ERGONOMY_H_

# ifndef	_STDLIB_H
#  include <stdlib.h>
# endif		/* _STDLIB_H */

# ifndef	_PARSER_H_
#  include "parser.h"
# endif		/* _PARSER_H_ */

typedef struct		s_loop
{
  t_alias		*alias;
  t_token		*token;
  struct s_loop		*next;
}			t_loop;

void		aff_prompt(void);

/* replace_aliases.c */
void		replace_aliases(t_token **tokens);
void		add_option_alias(char *option, t_token **pos);

/* aliases/modify_list.c */
int		modify_list(t_token **cpy_tok,
			    t_alias *alias, t_loop **loop);

/* aliases/free_aliases.c */
void		free_alias(void);

/* completion.c */
void		completion(char *buffer, size_t curs[2]);

#endif	/* _ERGONOMY_H_ */
