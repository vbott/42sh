/*
** strings.h for 42sh in /u/all/bereng_p/cu/public/42group/current/headers/lib_headers
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 10:29:04 2010 philippe berenguel
** Last update Mon May 10 15:12:41 2010 gianni castellani
*/

#ifndef		_STRINGS_H_
# define	_STRINGS_H_
# ifndef	_STDLIB_H_
#  include	<stdlib.h>
# endif		/* _STDLIB_H_ */

# ifndef	_GLOBBING_H_
#  include	"globbing.h"
# endif		/* _GLOBBING_H_ */

# define	NO_FREE		0
# define	FIRST_FREE	1
# define	ALL_FREE	2

char		*my_strdup(const char *s);
char		*my_strndup(const char *s, int size);
char		*my_strcdup(char *str, char c);
char		*my_strcat(int mode, ...);
size_t		my_strlen(const char *s);
char		**my_explode(char *str, char c);
char		*my_implode(char **);
int		char_find(char *str, char c);
int		my_strcmp(const char *s1, const char *s2);
int		my_strncmp(char *str, char *str2, int len);
int		my_strccmp(const char *s1, const char *s2, size_t len);
void		my_strcpy(char *str, char *str2);
int		len_tab(char **);
int		my_size_list(t_list *list);
void		my_swap(int **a, int **b);
int		my_atoi(const char *str);

#endif		/* _STRINGS_H_ */
