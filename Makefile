##
## Makefile for 42sh in /u/all/castel_a/cu/42sh/current
## 
## Made by gianni castellani
## Login   <castel_a@epitech.net>
## 
## Started on  Tue Mar 30 18:15:50 2010 gianni castellani
## Last update Sun May 23 23:33:47 2010 vivien botton
##

NAME	= 42sh

SRCS	= src/builtins/alias.c				\
	  src/builtins/bg.c				\
	  src/builtins/bind_key.c			\
	  src/builtins/bindkey_delete.c			\
	  src/builtins/cd.c				\
	  src/builtins/echo.c				\
	  src/builtins/env.c				\
	  src/builtins/env_arg.c			\
	  src/builtins/exit.c				\
	  src/builtins/fg.c				\
	  src/builtins/history.c			\
	  src/builtins/jobs.c				\
	  src/builtins/setenv.c				\
	  src/builtins/source.c				\
	  src/builtins/unalias.c			\
	  src/builtins/unsetenv.c			\
	  src/builtins/set.c				\
	  src/builtins/unset.c				\
	  src/ergonomy/aliases/free_alias.c		\
	  src/ergonomy/aliases/modify_list.c		\
	  src/ergonomy/aliases/replace_aliases.c	\
	  src/ergonomy/completion/aff.c			\
	  src/ergonomy/completion/aff_cases.c		\
	  src/ergonomy/completion/completion.c		\
	  src/ergonomy/completion/parsing.c		\
	  src/ergonomy/completion/part_completion.c	\
	  src/ergonomy/completion/part_comp_print.c	\
	  src/ergonomy/history/history.c		\
	  src/ergonomy/history/get_next_line.c		\
	  src/ergonomy/history/put_in_history.c		\
	  src/ergonomy/globbing/add_list.c		\
	  src/ergonomy/globbing/function_star.c		\
	  src/ergonomy/globbing/handle_backquote.c	\
	  src/ergonomy/globbing/handle_dollar.c		\
	  src/ergonomy/globbing/handle_env.c		\
	  src/ergonomy/globbing/handle_star.c		\
	  src/ergonomy/globbing/handle_tilde.c		\
	  src/ergonomy/globbing/list_in_str.c		\
	  src/ergonomy/globbing/match.c			\
	  src/ergonomy/globbing/my_explode_no_glob.c	\
	  src/ergonomy/globbing/my_sort_list_end.c	\
	  src/ergonomy/globbing/put_tab_in_list.c	\
	  src/ergonomy/interface/prompt.c		\
	  src/ergonomy/history/create_history.c		\
	  src/ergonomy/history/create_history_file.c	\
	  src/ergonomy/history/create_commandnode.c	\
	  src/ergonomy/history/delete_first_node.c	\
	  src/ergonomy/jobcontrol/free_jobs.c		\
	  src/ergonomy/jobcontrol/term_jobs.c		\
	  src/ergonomy/jobcontrol/jobslist.c		\
	  src/execution/cmd_find.c			\
	  src/execution/exec_child.c			\
	  src/execution/exec_conf.c			\
	  src/execution/exec_builtin.c			\
	  src/execution/handle_status.c			\
	  src/execution/hook_signal.c			\
	  src/execution/main.c				\
	  src/execution/init_42sh.c			\
	  src/execution/int_to_str.c			\
	  src/parser/cpy_env.c				\
	  src/parser/create_tree.c			\
	  src/parser/create_parenth_node.c		\
	  src/parser/exec_tree.c			\
	  src/parser/free_tree.c			\
	  src/parser/get_str_cmd.c			\
	  src/parser/handlers.c				\
	  src/parser/handle_background.c		\
	  src/parser/handle_or_and.c			\
	  src/parser/handle_parenthesis.c		\
	  src/parser/handle_redir.c			\
	  src/parser/handle_redir_error.c		\
	  src/parser/is_red.c				\
	  src/parser/lexer/and_or_error.c		\
	  src/parser/lexer/background_error.c		\
	  src/parser/lexer/command_error.c		\
	  src/parser/lexer/free_token_list.c		\
	  src/parser/lexer/handle_error.c		\
	  src/parser/lexer/is_redir.c			\
	  src/parser/lexer/is_token_separ.c		\
	  src/parser/lexer/lred_error.c			\
	  src/parser/lexer/move_red.c			\
	  src/parser/lexer/pipe_error.c			\
	  src/parser/lexer/rred_error.c			\
	  src/parser/lexer/lparenth_error.c		\
	  src/parser/lexer/rparenth_error.c		\
	  src/parser/lexer/semicolon_error.c		\
	  src/parser/lexer/switch_red.c			\
	  src/parser/lexer/token_list.c			\
	  src/parser/lexer/create_parenth_list.c	\
	  src/parser/lexer/replace_redirerr.c		\
	  src/termcaps/add_char.c			\
	  src/termcaps/free_bindkey.c			\
	  src/termcaps/free_termcap.c			\
	  src/termcaps/init_bindkey.c			\
	  src/termcaps/init_cap.c			\
	  src/termcaps/load_bind.c			\
	  src/termcaps/load_bind2.c			\
	  src/termcaps/load_bind3.c			\
	  src/termcaps/my_cursorbackspace.c		\
	  src/termcaps/my_cursorclear.c			\
	  src/termcaps/my_cursordelete.c		\
	  src/termcaps/my_cursorend.c			\
	  src/termcaps/my_cursorhome.c			\
	  src/termcaps/my_cursorleft.c			\
	  src/termcaps/my_cursorright.c			\
	  src/termcaps/my_cursorinterrupt.c		\
	  src/termcaps/my_outc.c			\
	  src/termcaps/no_canonical_mode.c		\
	  src/termcaps/resize_window.c			\
	  src/termcaps/termcap.c

OBJS	= $(SRCS:.c=.o)

CC	= clang 

RM	= rm -f

LIB42	= src/libs/lib42.a

LIBS	= -lreadline -lncursesw -L src/libs/ -l42

CFLAGS	+= -ansi -pedantic -Wall -Wextra -Wstrict-prototypes -pipe -I include/

lib	: $(LIBS42)
	$(MAKE) -C src/libs
	$(MAKE) $(NAME)

$(NAME)	: $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS)

all	: lib

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re	: fclean all

.c.o	:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
