/*
** main.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat May  1 17:06:54 2010 gianni castellani
** Last update Sun May 23 15:51:18 2010 gianni castellani
*/

#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/free.h"
#include "lib_includes/env.h"
#include "builtins.h"
#include "ergonomy.h"
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "execution.h"
#include "gl_vars.h"

t_global		gl_global;
t_termcap		gl_cap;

void			sigwinch(int sig)
{
  struct winsize	w;
  int			co;

  (void)sig;
  co = gl_cap.co;
  gl_cap.co = -1;
  xioctl(0, TIOCGWINSZ, &w);
  gl_cap.co = w.ws_col;
  if (gl_global.buffer)
    resize_window(co, gl_cap.co);
  xsignal(SIGWINCH, sigwinch);
}

void			init_exec(t_exec *exec, t_lpid **lpid)
{
  exec->background = 0;
  exec->pipe = 0;
  exec->parenthesis = 0;
  exec->fd[0] = -1;
  exec->fd[1] = -1;
  exec->fd[2] = -1;
  *lpid = NULL;
}

void			launch_cmd(char *buf, int history)
{
  t_exec		exec;
  t_lpid		*lpid;
  t_tree		*tree;
  t_token		*token;

  init_exec(&exec, &lpid);
  token = create_token_list(buf);
  replace_redirerr(token);
  if (history)
    put_in_history(token);
  replace_aliases(&token);
  move_red(&token);
  if (handle_error(token) == EXIT_FAILURE)
    {
      free_token_list(token);
      return ;
    }
  swap_rred(&token, 0);
  swap_lred(&token, 0);
  tree = create_tree(token);
  if (gl_global.normal_tty)
    xioctl(STDIN_FILENO, TIOCSETA, &gl_global.oldterm);
  exec_tree(tree, &lpid, &exec);
  if (gl_global.normal_tty)
    xioctl(STDIN_FILENO, TIOCSETA, &gl_global.newterm);
}

int			no_command(char *buf)
{
  int			i;

  i = 0;
  while (buf[i] != '\0')
    {
      if (buf[i] != ' ' && buf[i] != '\t')
	{
	  if (buf[i] == '#')
	    return (0);
	  return (1);
	}
      i++;
    }
  return (0);
}

int			main(void)
{
  char			buf[4096];
  int			termcap;

  init_shell(&termcap, &gl_global.newterm, &gl_global.oldterm);
  if (!termcap)
    exec_conf(STDIN_FILENO, 1);
  else
    {
      xioctl(0, TIOCSETA, &gl_global.newterm);
      while (42)
	{
	  buf[0] = '\0';
	  aff_prompt();
	  my_read(buf);
	  if (no_command(buf))
	    launch_cmd(buf, WITH_HIST);
	  print_term_jobs(1);
	}
    }
  quit(NULL);
  return (EXIT_SUCCESS);
}
