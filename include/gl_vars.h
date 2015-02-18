/*
** gl_vars.h for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Apr 17 14:01:46 2010 gianni castellani
** Last update Wed May 19 19:50:20 2010 gianni castellani
*/

#ifndef		_GL_VARS_H_
# define	_GL_VARS_H_

# ifndef	_PARSER_H_
#  include "parser.h"
# endif		/* _PARSER_H_ */

# ifndef	_BUILTINS_H_
#  include "builtins.h"
# endif		/* _BUILTINS_H_ */

# ifndef	_HISTORY_H_
#  include "history.h"
# endif		/* _HISTORY_H_ */

# ifndef	_JOBS_H_
#  include "jobs.h"
# endif		/* _JOBS_H_ */

# ifndef	_TERMCAPS_H_
#  include "termcaps.h"
# endif		/* _TERMCAPS_H_ */

typedef struct		s_global
{
  char			**gl_env;
  t_local		*gl_local;
  t_bindkey		*gl_bindkey;
  t_history		*history;
  t_history		*begin_hist;
  int			hist_len;
  t_jobs		*gl_jobs;
  size_t		prompt_len;
  char			*buffer;
  size_t		*curs_pos;
  int			normal_tty;
  t_alias		*gl_alias;
  t_termios		newterm;
  t_termios		oldterm;
}			t_global;

#endif		/* _GL_VARS_H_ */
