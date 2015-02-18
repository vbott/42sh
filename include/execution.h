/*
** execution.h for 42sh in /u/all/bereng_p/cu/public/42group/test_backup/headers
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Thu Mar 18 16:42:32 2010 philippe berenguel
** Last update Thu May  6 11:34:17 2010 vivien botton
*/

#ifndef			_EXECUTION_H_
# define		_EXECUTION_H_

# ifndef                 _TERMCAPS_H_
#  include "termcaps.h"
# endif			/* _TERMCAPS_H_ */

# define		WITH_HIST 1
# define		WITHOUT_HIST 0

typedef struct		s_builtin
{
  char			*name;
  int			(*func)(char **);
}			t_builtin;

typedef struct		s_signal
{
  int			sig;
  char			*error;
}			t_signal;

int	error_msg(char *name, char *err, int value);
char	*get_signal(int);
void	hook_signal(void);
void	unhook_signal(void);
int	handle_status(int father, int *status, int taketty, int bg);
int	cmd_find(char ** cmd, t_exec *exec, t_lpid *lpid);
void	launch_cmd(char *buf, int history);
int	no_command(char *buf);
char	*get_next_line(int fd);
void	exec_conf(int fd, int job);
char	*int_to_str(int nb, char *str);

/* exec_child.c */
void	change_pgid(t_exec *exec, t_lpid *lpid);
void	exec_child(char *cmd, char **args, t_exec *exec, t_lpid *lpid);
void	dup_fd(int fd[3]);
void	close_fd(int fd[3]);

/* exec_builtin.c */
int	builtin_find(char **cmd, t_exec *exec, t_lpid *lpid, int *found);

/* init_42sh.c*/
void	init_shell(int *termcap, t_termios *newterm, t_termios *oldterm);

#endif			/* _EXECUTION_H_ */
