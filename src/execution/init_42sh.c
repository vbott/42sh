/*
** init_42sh.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed May 12 11:00:40 2010 cerisier mickael
** Last update Sat May 22 19:43:01 2010 gianni castellani
*/

#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include "builtins.h"
#include "ergonomy.h"
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "execution.h"
#include "history.h"
#include "gl_vars.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/env.h"

extern t_global		gl_global;

static void		retrieve_var(char *path)
{
  char			*file;
  char			*tab[4];
  char			buffer[12];

  add_local("PATH", my_getenv("PATH"));
  add_local("HOME", path);
  add_local("HISTSIZE", int_to_str(HIST_LIMIT, buffer));
  file = my_strcat(NO_FREE, path, "/.42sh_history", NULL);
  if (file)
    {
      add_local("HISTFILE", file);
      free(file);
    }
  if (my_getenv("PWD") == NULL)
    {
      tab[0] = "setenv";
      tab[1] = "PWD";
      tab[2] = xgetcwd(0, 0);
      tab[3] = NULL;
      my_setenv(tab);
    }
}

static char		*init_shell_2(void)
{
  char			*path;

  hook_signal();
  gl_global.buffer = NULL;
  gl_global.curs_pos = NULL;
  gl_global.gl_local = NULL;
  gl_global.gl_env = cpy_env();
  gl_global.normal_tty = isatty(STDIN_FILENO);
  path = hist_find_path();
  retrieve_var(path);
  return (path);
}

static void		init_term(int *termcap, t_termios *newterm,
				  t_termios *oldterm)
{
  no_canonic_mode(newterm, oldterm, termcap);
  if (*termcap)
    {
      init_cap(termcap);
      sigwinch(0);
    }
  else
    gl_global.normal_tty = 0;
  if (*termcap)
    init_bindkey();
}

static void		load_history(void)
{
  char			*file;
  int			fd;

  file = my_getlocal("HISTFILE");
  if (file)
    {
      fd = xopen(file, O_RDWR | O_CREAT,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IRWXO);
      if (fd != -1)
	{
	  gl_global.history = create_history(fd);
	  xclose(fd);
	}
    }
}

void			init_shell(int *termcap, t_termios *newterm,
				   t_termios *oldterm)
{
  char			*path;
  char			*file;
  int			fd;

  path = init_shell_2();
  gl_global.gl_jobs = NULL;
  gl_global.gl_alias = NULL;
  *termcap = gl_global.normal_tty;
  if (*termcap)
    init_term(termcap, newterm, oldterm);
  file = my_strcat(FIRST_FREE, path, "/.42shrc", NULL);
  if (gl_global.normal_tty &&
      (fd = xopen(file, O_RDONLY | O_CREAT, 0644)) != -1)
    {
      exec_conf(fd, 0);
      xclose(fd);
    }
  free(file);
  load_history();
}
