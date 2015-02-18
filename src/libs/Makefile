##
## Makefile for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh/libs/free_funcs
## 
## Made by philippe berenguel
## Login   <bereng_p@epitech.net>
## 
## Started on  Fri Apr  2 13:37:44 2010 philippe berenguel
## Last update Sun May 23 23:33:58 2010 vivien botton
##

NAME	= lib42.a
SRCS	= aff_funcs/my_putchar.c	\
	  aff_funcs/my_puterror.c	\
	  aff_funcs/my_putnbr.c		\
	  aff_funcs/my_putstr.c		\
	  aff_funcs/my_putnstr.c	\
	  env_funcs/my_getenv.c		\
	  free_funcs/free_tab.c		\
	  string_funcs/char_find.c	\
	  string_funcs/len_tab.c	\
	  string_funcs/my_atoi.c	\
	  string_funcs/my_explode.c	\
	  string_funcs/my_implode.c	\
	  string_funcs/my_size_list.c	\
	  string_funcs/my_sort_list.c	\
	  string_funcs/my_strcat.c	\
	  string_funcs/my_strccmp.c	\
	  string_funcs/my_strcdup.c	\
	  string_funcs/my_strcmp.c	\
	  string_funcs/my_strdup.c	\
	  string_funcs/my_strndup.c	\
	  string_funcs/my_strlen.c	\
	  string_funcs/my_strncmp.c	\
	  string_funcs/my_strcpy.c	\
	  string_funcs/my_swap.c	\
	  xfunctions/xchdir.c		\
	  xfunctions/xclose.c		\
	  xfunctions/xclosedir.c	\
	  xfunctions/xdup2.c		\
	  xfunctions/xdup.c		\
	  xfunctions/xexecve.c		\
	  xfunctions/xfork.c		\
	  xfunctions/xgetcwd.c		\
	  xfunctions/xglob.c		\
	  xfunctions/xioctl.c		\
	  xfunctions/xkill.c		\
	  xfunctions/xmalloc.c		\
	  xfunctions/xopen.c		\
	  xfunctions/xopendir.c		\
	  xfunctions/xpipe.c		\
	  xfunctions/xsignal.c		\
	  xfunctions/xread.c		\
	  xfunctions/xreaddir.c		\
	  xfunctions/xstat.c		\
	  xfunctions/xsignal.c		\
	  xfunctions/xsetpgid.c		\
	  xfunctions/xtcsetpgrp.c	\
	  xfunctions/xtgetstr.c		\
	  xfunctions/xtputs.c		\
	  xfunctions/xwaitpid.c		\
	  xfunctions/xwrite.c

OBJS	= $(SRCS:.c=.o)
CC	= gcc
CFLAGS	+= -Wall -Wextra -pedantic -Wstrict-prototypes -ansi -I ../../include
AR	= ar r
RM	= rm -f
RANLIB	= ranlib

$(NAME)	: $(OBJS)
	$(AR) $(NAME) $(OBJS)
	$(RANLIB) $(NAME)

all	: $(NAME)

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re	: fclean all

.c.o	:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)