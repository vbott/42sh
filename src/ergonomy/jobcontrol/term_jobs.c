/*
** jobs.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:42:30 2010 cerisier mickael
** Last update Sat May 22 17:57:37 2010 vivien botton
*/

#include <sys/wait.h>
#include <signal.h>
#include "parser.h"
#include "execution.h"
#include "jobs.h"
#include "termcaps.h"
#include "gl_vars.h"
#include "lib_includes/xfunctions.h"

extern t_global	gl_global;

static void		update_job(t_lpid *cpy, t_jobs *job,
				   int *res, const int status)
{
  if (*res == EXIT_SUCCESS && *res != STOPPED)
    {
      job->status = (!WIFSTOPPED(status)) ? status : STOPPED;
      *res = job->status;
    }
  if (!WIFSTOPPED(status))
    cpy->done = 1;
}

static void		pipe_term_jobs(t_jobs *job)
{
  t_lpid	*cpy;
  int		r;
  int		res;
  int		status;

  cpy = job->pids;
  status = -1;
  res = EXIT_SUCCESS;
  while (cpy)
    {
      if (cpy->done == 0)
	{
	  if ((r = xwaitpid(cpy->pid, &status, WNOHANG | WUNTRACED)) != -1 && r)
	    update_job(cpy, job, &res, status);
	  else
	    status = -1;
	}
      cpy = cpy->next;
    }
  if (status != -1 || res != EXIT_SUCCESS)
    print_job(job, 0);
  del_job(job->pids, 0);
}

void		print_term_jobs(const int verbose)
{
  t_jobs	*cpy;
  t_jobs	*next;
  int		stat;
  int		r;

  cpy = gl_global.gl_jobs;
  while (cpy)
    {
      next = cpy->next;
      if (!cpy->pids)
	{
	  r = xwaitpid(cpy->pgid, &stat, WNOHANG | WUNTRACED);
	  if (r != -1 && r)
	    {
	      cpy->status = (WIFSTOPPED(stat)) ? STOPPED : WEXITSTATUS(stat);
	      if (verbose)
		print_job(cpy, 0);
	      if (!WIFSTOPPED(stat))
		set_job(cpy->pgid, TERMINATED);
	    }
	}
      else
      	pipe_term_jobs(cpy);
      cpy = next;
    }
}
