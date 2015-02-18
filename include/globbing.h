/*
** globbing.h for  in /u/all/caille_c/cu/42sh/current/headers
** 
** Made by carole cailleux
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr  1 15:19:22 2010 carole cailleux
** Last update Sun May  2 12:36:06 2010 gianni castellani
*/

#ifndef		_GLOBBING_H_
# define	_GLOBBING_H_

# ifndef	__PARSER_H_
#  include "parser.h"
# endif		/*__PARSER_H_*/

# define	WITH_ENV_LOCAL 2
# define	WITH_ENV 1
# define	WITHOUT_ENV 0

typedef struct	s_list
{
  char		*data;
  struct s_list	*next;
}		t_list;

int	handle_dollar(char **buff);
int	handle_tilde(char **args, int mode);

/* add_list.c */
t_list	*add_list(char *str, t_list *list);
t_list	*add_list_star(char *str, t_list *list, int mode);

/* handle_backquote.c */
t_list	*handle_backquote(char *str, t_list *list, int env);

/* handle_env.c */
t_list	*add_list_env(char *str, t_list *list);

/* handle_star.c */
int	char_find_str(char *str, char *c);
t_list	*handle_star_list(char *str, t_list *list, int env);
char	**handle_star(char **args, int env);

/* function.c */
char	*get_path(char *str, int *size);
char	*get_temp(char *name, char *path);
char	**put_list_in_tab(t_list *list);

/* list_in_str.c */
char	*list_in_str(t_list *list);

/* match.c */
int	match(char *s1, char *s2);

/* my_explode_no_globc */
char	**my_explode_no_glob(char *str);

/* my_sort_list_end.c */
void	my_sort_list_end(t_list **begin, t_list *end);

/* put_tab_in_list.c */
t_list	*put_tab_in_list(char **titi, t_list *grominet);

#endif		/* _GLOBBING_H_ */
