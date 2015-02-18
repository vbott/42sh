/*
** parser.h for 42sh in /u/epitech_2014/bereng_p/public/42group/current/headers
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Mar 13 18:28:59 2010 gianni castellani
** Last update Sun May 23 15:45:11 2010 gianni castellani
*/

#ifndef		_PARSER_H_
# define	_PARSER_H_

# define T_SEMICOLON	1
# define T_RRED		2
# define T_LRED		4
# define T_DRRED	8
# define T_DLRED	16
# define T_ANDRED	32
# define T_ANDDRED	64
# define T_NUMRED	128
# define T_PIPE		256
# define T_AND		512
# define T_OR		1024
# define T_COMMAND	2048
# define T_IS_RIGHT	4096
# define T_BACKGROUND	8192
# define T_LPARENTH	16384
# define T_RPARENTH	32768

# define MODE_OPEN	0644

# define UNUSED __attribute__ ((unused))

typedef struct		s_tree
{
  int			type;
  int			free;
  char			*data;
  struct s_tree		*left;
  struct s_tree		*right;
}			t_tree;

typedef struct		s_token
{
  int			type;
  int			free;
  char			*data;
  struct s_token	*next;
}			t_token;

typedef struct		s_prioop
{
  int			len;
  char			*data;
  int			type;
  int			prio;
  int			(*func)(t_token *cur_token, int *mask);
}			t_prioop;

typedef struct		s_lpid
{
  int			pid;
  int			done;
  struct s_lpid		*next;
}			t_lpid;

typedef struct		s_exec
{
  int			background;
  int			pipe;
  int			parenthesis;
  int			fd[3];
}			t_exec;

typedef	struct		s_vfunc
{
  int			data;
  int			(*func)(t_tree *tree, t_lpid **lpid, t_exec *exec);
}			t_vfunc;

/* cpy_env.c */
char	**cpy_env(void);

/* create_parenth_node.c */
t_tree	*create_parenth_node(t_tree *ret, t_token *token);

/* create_tree.c */
t_token	*find_priority(t_token *token);
char	*get_name_file(char *str, int cpt, int i);
char	*modif_str(char *str, int i, int cpt);
t_tree	*create_tree(t_token *token);

/* exec_tree.c */
t_lpid	*add_pid(int pid, t_lpid *lpid);
int	handle_background(t_tree *tree, t_lpid **lpid, t_exec *exec);
int	exec_command(t_tree *tree, t_lpid **lpid, t_exec *exec);
int	exec_tree(t_tree *tree, t_lpid **lpid, t_exec *exec);

/* free_token_list.c */
void	free_token_list(t_token *token);

/* free_tree.c */
void	free_tree(t_tree *tree);

/* get_str_cmd.c */
char	*get_str_cmd(char *cmd, t_tree *tree);

/* handle_background.c */
int	handle_background(t_tree *tree, t_lpid **lpid, t_exec *exec);

/* handle_or_and.c */
int	handle_or(t_tree *tree, t_lpid **lpid, t_exec *exec);
int	handle_and(t_tree *tree, t_lpid **lpid, t_exec *exec);

/* handle_parenthesis.c */
int	handle_parenthesis(t_tree *tree, t_lpid **lpid, t_exec *exec);

/* handle_redir.c */
int	handle_redir_right(t_tree *tree, t_lpid **lpid, t_exec *exec);
int	handle_redir_left(t_tree *tree, t_lpid **lpid, t_exec *exec);

/* handle_redir_error.c */
int	handle_redir_error(t_tree *tree, t_lpid **lpid, t_exec *exec);

/* handlers.c */
int	handle_wait_pipe(t_lpid *lpid, int bg);
int	handle_pipe(t_tree *tree, t_lpid **lpid, t_exec *exec);
int	handle_semicolon(t_tree *tree, t_lpid **lpid, t_exec *exec);

/* handle error */

int	handle_error(t_token *token);
int	semicolon_error(t_token *cur_token, int *mask);
int	pipe_error(t_token *cur_token, int *mask);
int	rred_error(t_token *cur_token, int *mask);
int	lred_error(t_token *cur_token, int *mask);
int	and_or_error(t_token *cur_token, int *mask);
int	background_error(t_token *cur_token, int *mask);
int	lparenth_error(t_token *cur_token, int *mask);
int	rparenth_error(t_token *cur_token, int *mask);
int	command_error(t_token *cur_token, int *mask);
void	move_red(t_token **token);

/* is_redir.c */
int	is_redir(int type);

/* is_token_separ.c */
int	is_token_separ(int type);

/* token_list.c */
t_token	*create_token_list(char *str);

/* switch_token.c */
void	swap_rred(t_token **token, int i);
void	swap_lred(t_token **token, int i);

/* create_parenth_list.c */
int	check_between_parenthesis(t_token **token, int *mask);

/* replace_redirerr.c */
int			replace_redirerr(t_token *token);

#endif		/* _PARSER_H_ */
