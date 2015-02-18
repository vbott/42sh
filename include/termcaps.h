/*
** termcaps.h for 42sh in /u/all/castel_a/cu/svn/current/headers
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Mar 20 10:53:33 2010 gianni castellani
** Last update Wed May 19 19:44:10 2010 gianni castellani
*/

#ifndef			_TERMCAPS_H_
# define		_TERMCAPS_H_

# ifndef	_STDLIB_H
#  include <stdlib.h>
# endif		/* _STDLIB_H */

# ifndef	_TERMIOS_H
#  include <termios.h>
# endif		/* _TERMIOS_H */

# define SIZE_AREA	4096
# define SIZE_BP	1024

# define ASC_ENTER	10
# define ASC_DEL	8

# ifndef TIOCGETA
#  define TIOCGETA	TCGETS
# endif

# ifndef TIOCSETA
#  define TIOCSETA	TCSETS
# endif

# ifndef TIOCGWINSZ
#  define TIOCGWINSZ	TCGWINSZ
# endif

# ifndef EOF
#  define EOF		"\04"
# endif /* EOF */

# define CTRLC		"\03"

typedef struct		termios	t_termios;

typedef struct		s_bindkey
{
  char			*ch;
  void			(*function)(char *, size_t *);
  char			*exec;
  struct s_bindkey	*next;
}			t_bindkey;

typedef struct		s_termcap
{
  int			co;
  char			*clstr;
  char			bp[SIZE_BP];
  char			*term;
  char			area[SIZE_AREA];
  char			*kustr;
  char			*kdstr;
  char			*klstr;
  char			*krstr;
  char			*kbstr;
  char			*kDstr;
  char			*khstr;
  char			*kestr;
  char			*cestr;
}			t_termcap;

int			my_outc(int);
void			sigwinch(int sig);
void			no_canonic_mode(t_termios *newterm,
					t_termios *oldterm, int *termcap);
void			init_bindkey(void);
void			free_bindkey(void);
void			free_termcap(void);
void			bk_handledelete(char *str);
void			init_cap(int *termcap);
void			resize_window(size_t old, size_t new);
void			my_cursor_left(char *buf, size_t i[2]);
void			my_cursor_right(char *buf, size_t i[2]);
void			my_read(char *buf);
void			my_cursor_home(char *buf, size_t i[2]);
void			my_cursor_end(char *buf, size_t i[2]);
void			my_cursor_backspace(char *buf, size_t i[2]);
void			my_cursor_delete(char *buf, size_t i[2]);
void			my_cursor_clear(char *buf, size_t i[2]);
void			my_cursor_interrupt(char *buf, size_t i[2]);
void			add_char(char *buf, char *ch, size_t i[2]);
void			deplace_cursor(size_t i[2]);
void			begin_cursor(size_t i[2]);
t_bindkey		*load_cursor_left(t_bindkey *temp);
t_bindkey		*load_cursor_right(t_bindkey *temp);
t_bindkey		*load_cursor_backspace(t_bindkey *temp);
t_bindkey		*load_cursor_delete(t_bindkey *temp);
t_bindkey		*load_cursor_home(t_bindkey *temp);
t_bindkey		*load_cursor_end(t_bindkey *temp);
t_bindkey		*load_cursor_clear(t_bindkey *temp);
t_bindkey		*load_cursor_completion(t_bindkey *temp);
t_bindkey		*load_cursor_history_up(t_bindkey *temp);
t_bindkey		*load_cursor_history_down(t_bindkey *temp);
t_bindkey		*load_cursor_eof(t_bindkey *temp);
t_bindkey		*load_cursor_interrupt(t_bindkey *temp);

#endif		/* !_TERMCAPS_H_ */
