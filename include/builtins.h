/*
** builtins.h for 42sh in /u/all/bereng_p/cu/rendu/SVN/svn/current/headers
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sat Mar 20 18:44:43 2010 philippe berenguel
** Last update Wed Apr 28 11:28:37 2010 cerisier mickael
*/

#ifndef		_BUILTINS_H_
# define	_BUILTINS_H_

typedef struct		s_alias
{
  char			*assign;
  char			*value;
  int			modify;
  struct s_alias	*next;
}			t_alias;

typedef struct		s_local
{
  char			*name;
  char			*value;
  struct s_local	*next;
}			t_local;

typedef struct		s_echo
{
  char			c;
  char			*str;
}			t_echo;

/* alias.c */
int		my_alias(char **cmd);
int		exist(char *assign, char *completevalue);

/* unalias.c */
int		unalias(char **args);

/* bind_key.c */
int		bind_key(char **cmd);

/* cd.c */
int		check_path(char *path);
char		*find_tmp_path(char *path_tmp);
int		cd(char **cmd);

/* env.c */
int		aff_env(char **cmd);

/* env_arg.c */
int		argument_parser(char **cmd, int *option);

/* echo.c */
int		echo(char **cmd);

/* history.c */
int		history(char **cmd);

/* my_setenv.c */
int		my_setenv(char **cmd);

/* my_unsetenv.c */
int		my_unsetenv(char **cmd);

/* local.c */
int		set(char **cmd);
int		unset(char **cmd);
void		add_local(const char *name, const char *value);
char		*my_getlocal(const char *name);
void		free_local(void);

/* jobs.c */
int		jobs(char **cmd);

/* fg.c */
int		fg(char **cmd);

/* bg.c */
int		bg(char **cmd);

/* bind_key.c */
int		bind_key(char **cmd);

/* quit.c */
int		quit(char **cmd);

/* source.c */
int		source(char **cmd);

#endif		/* _BUILTINS_H_ */
