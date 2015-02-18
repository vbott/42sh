/*
** handle_status.c for 42sh in /u/all/bereng_p/cu/rendu/SVN/svn/current/execution
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 21 12:34:18 2010 philippe berenguel
** Last update Sat May 22 17:49:56 2010 gianni castellani
*/

#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "jobs.h"
#include "execution.h"
#include "builtins.h"
#include "gl_vars.h"
#include "lib_includes/aff.h"
#include "lib_includes/xfunctions.h"

static const t_signal	gl_signal[] = {
  {SIGFPE, "Floating point exception"},
  {SIGSEGV, "Segmentation fault"},
  {SIGABRT, "Aborted"},
  {SIGBUS, "Bus error"},
  {SIGQUIT, "Quit"},
  {SIGPIPE, "Broken pipe"},
  {SIGILL, "Illegal instruction"},
  {SIGTERM, "Terminated"},
  {SIGUSR1, "User-defined signal 1"},
  {SIGUSR2, "User-defined signal 2"},
  {SIGHUP, "Hangup"},
  {SIGKILL, "Killed"},
  {SIGPROF, "Profiling timer expired"},
  {SIGXCPU, "CPU time limit exceeded"},
  {SIGXFSZ, "File size limit exceeded"},
  {SIGVTALRM, "Virtual timer expired"},
  {SIGTRAP, "Trace/breakpoint trap"},
  {SIGALRM, "Alarm clock"},
  {SIGSYS, "Bad system call"},
  {SIGIO, "I/O possible"},
  {SIGSTOP, "Stopped"},
  {SIGTSTP, "Stopped"},
  {SIGTTIN, "Stopped : tty input for background process"},
  {SIGTTOU, "Stopped : tty output for background process"},
#if defined SIGPOLL
  {SIGPOLL, "I/O possible"},
#endif /* !SIGPOLL */
#if defined SIGPWR
  {SIGPWR, "Power failure"},
#endif /* !SIGPWR */
#if defined SIGSTKFLT
  {SIGSTKFLT, "Stack fault"},
#endif /* !SIGSTKFLT */
  {0, 0}
};

extern t_global	gl_global;

static void	signals(int status)
{
  int		sig;
  int		i;

  sig = WTERMSIG(status);
  i = 0;
  while (gl_signal[i].error)
    {
      if (sig == gl_signal[i].sig)
	{
	  my_puterror(gl_signal[i].error);
#if defined WCOREDUMP
	  if (WCOREDUMP(status))
	    my_puterror(" (core dumped)");
#endif /* !WCOREDUMP */
	  my_puterror("\n");
	  return ;
	}
      i++;
    }
}

char		*get_signal(int status)
{
  int		sig;
  int		i;

  if (WIFEXITED(status))
    return ("Done");
  else if (WIFCONTINUED(status))
    return ("Continued");
  else if (WIFSIGNALED(status) || WIFSTOPPED(status))
    {
      sig = (WIFSIGNALED(status)) ?
	WTERMSIG(status) : WSTOPSIG(status);
      i = 0;
      while (gl_signal[i].error)
	{
	  if (sig == gl_signal[i].sig)
	    return (gl_signal[i].error);
	  i++;
	}
    }
  return (NULL);
}

void		set_returnvalue(int status)
{
  char		buffer[12];

  add_local("?", int_to_str(status, buffer));
}

int		handle_status(int father, int *status, int taketty, int bg)
{
  int		flag;

  flag = (bg) ? 0 : WUNTRACED;
  if (xwaitpid(father, status, flag) != -1)
    {
      set_returnvalue(*status);
      if (taketty && !bg && gl_global.normal_tty)
	xtcsetpgrp(STDIN_FILENO, getpid());
      if (WIFSTOPPED(*status) && !bg)
	{
	  if (taketty)
	    change_last(-1, getpgid(father));
	  my_putchar('\n');
	  set_job(getpgid(father), STOPPED);
	  return (EXIT_SUCCESS);
	}
      else if (WIFSIGNALED(*status) && !bg)
	signals(*status);
      if (taketty && !bg)
	set_job(father, TERMINATED);
      return (EXIT_SUCCESS);
    }
  if (taketty && gl_global.normal_tty)
    xtcsetpgrp(0, getpid());
  return (EXIT_FAILURE);
}
