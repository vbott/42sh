/*
** history.h for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Apr 17 17:58:10 2010 gianni castellani
** Last update Sun May 23 16:09:47 2010 gianni castellani
*/

#ifndef		_HISTORY_H_
# define	_HISTORY_H_

# ifndef	_STDLIB_H
#  include <stdlib.h>
# endif		/* _STDLIB_H */

# ifndef	_PARSER_H_
#  include "parser.h"
# endif		/* _PARSER_H_ */

# define	BUFF_SIZE 256
# define	READ_SIZE 256
# define	HIST_LIMIT 500

typedef struct		s_history
{
  char			*data;
  struct s_history	*prev;
  struct s_history	*next;
}			t_history;

void			hist_up(char *buf, size_t i[2]);
void			hist_down(char *buf, size_t i[2]);
void			put_in_history(t_token *token);
char			*hist_find_path(void);
t_history		*create_history(int fd);
void			create_commandnode(void);
void			delete_commandnode(void);
void			create_history_file(void);
void			delete_first_node(void);
int                     get_histsize(void);

#endif		/* !_HISTORY_H_ */
