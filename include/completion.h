/*
** completion.h for  in /u/all/caille_c/cu/42sh/current/headers
** 
** Made by carole cailleux
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr  1 15:18:44 2010 carole cailleux
** Last update Sun May 23 23:16:42 2010 philippe berenguel
*/

#ifndef		_COMPLETION_H_
# define	_COMPLETION_H_

typedef struct	s_info
{
  int		mode;
  char		**path;
  char		*to_match;
  char		*to_free;
}		t_info;

typedef struct s_part
{
  int		s;
  int		c;
  int		t;
  int		i;
  char		**new_tab;
}		t_part;

void		aff(char **tab, char *buffer, size_t *curs, t_info *info);
void		cd_case(char **tab);
void		tilde_case(int *p, int *n, int *t, char **tab);
void		tilde_case_two(char **tab, char *buffer, size_t *curs);
int		hidden_files(char *buffer, int *c, int *s, size_t *curs);
int		no_hidden_files(char *buffer, int *c, int *s);
char		*parsing(char *str, int *mode);
void		part_completion(char **tab, char *buffer, size_t *curs,
				t_info *info);
void		choose_printing(t_part *p, t_info *info, char *buffer,
				size_t *curs);

#endif		/* _COMPLETION_H_ */
