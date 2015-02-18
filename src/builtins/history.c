/*
** history.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun Apr 18 12:00:25 2010 gianni castellani
** Last update Sun May 23 16:36:25 2010 gianni castellani
*/

#include <fcntl.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"
#include "lib_includes/aff.h"
#include "lib_includes/env.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

void			display_hist(void)
{
  extern t_global	gl_global;
  int			cpt;

  if (gl_global.history)
    {
      cpt = 1;
      while (gl_global.history->next)
	gl_global.history = gl_global.history->next;
      while (gl_global.history->prev)
	{
	  my_putnbr(cpt);
	  my_putstr(" ");
	  my_putstr(gl_global.history->data);
	  my_putstr("\n");
	  gl_global.history = gl_global.history->prev;
	  cpt++;
	}
      my_putnbr(cpt);
      my_putstr(" ");
      my_putstr(gl_global.history->data);
      my_putstr("\n");
    }
}

char			*hist_find_path(void)
{
  extern t_global	gl_global;
  int			uid;
  struct passwd		*pass;
  char			buf[4096];
  char			*str;

  str = my_getenv("HOME");
  if (str != NULL)
    return (my_strdup(str));
  pass = xmalloc(sizeof(*pass));
  uid = getuid();
  if (getpwuid_r(uid, pass, buf, sizeof(buf), &pass) == -1)
    perror("getpwuid_r");
  else
    str = my_strdup(pass->pw_dir);
  free(pass);
  return (str);
}

void			delete_hist(void)
{
  extern t_global	gl_global;
  t_history		*hist;

  gl_global.hist_len = 0;
  while (gl_global.history->next)
    gl_global.history = gl_global.history->next;
  while (gl_global.history->prev)
    {
      hist = gl_global.history;
      gl_global.history = gl_global.history->prev;
      free(hist->data);
      free(hist);
    }
  free(gl_global.history->data);
  free(gl_global.history);
  gl_global.history = NULL;
  gl_global.begin_hist = NULL;
}

int			history(char **cmd)
{
  extern t_global	gl_global;

  if (!cmd[1])
    {
      display_hist();
      return (EXIT_SUCCESS);
    }
  else if (!my_strcmp(cmd[1], "-c") && !cmd[2])
    {
      delete_hist();
      return (EXIT_SUCCESS);
    }
  my_puterror("Usage: history [options]\nOptions: -c: clear history.\n");
  return (EXIT_FAILURE);
}
