/*
** hook_signal.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 15:13:53 2010 gianni castellani
** Last update Wed Apr 28 15:46:05 2010 botton vivien
*/

#include <stdlib.h>
#include <signal.h>
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"
#include "lib_includes/xfunctions.h"

void			hook_signal(void)
{
  xsignal(SIGWINCH, sigwinch);
  xsignal(SIGQUIT, SIG_IGN);
  xsignal(SIGINT, SIG_IGN);
  xsignal(SIGTSTP, SIG_IGN);
  xsignal(SIGTTOU, SIG_IGN);
}

void			unhook_signal(void)
{
  extern t_global	gl_global;

  gl_global.gl_jobs = NULL;
  xsignal(SIGINT, SIG_DFL);
  xsignal(SIGQUIT, SIG_DFL);
  xsignal(SIGTSTP, SIG_DFL);
  xsignal(SIGTTOU, SIG_DFL);
  xsignal(SIGWINCH, SIG_DFL);
}
