/*
** exit.c for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 14:49:19 2010 philippe berenguel
** Last update Sun May 23 21:10:27 2010 vivien botton
*/

#include <stdlib.h>
#include "builtins.h"
#include "ergonomy.h"
#include "lib_includes/free.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"

extern t_alias		*gl_aliases;

int			quit(UNUSED char **cmd)
{
  extern t_global	gl_global;
  int			i;

  i = 0;
  free_bindkey();
  free_termcap();
  free_tab(gl_global.gl_env);
  free_jobs(gl_global.gl_jobs);
  create_history_file();
  free_local();
  free_alias();
  exit(EXIT_SUCCESS);
}
