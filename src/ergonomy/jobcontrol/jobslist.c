/*
** jobslist.c for  in /u/all/caille_c/cu/42sh/current/ergonomy/jobcontrol
** 
** Made by carole cailleux
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr  1 15:17:35 2010 carole cailleux
** Last update Fri May 21 16:52:26 2010 vivien botton
*/

#include <stdlib.h>
#include <unistd.h>
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"
#include "signal.h"
#include "execution.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

extern t_global	gl_global;

void		add_job(int pid, char *cmd, t_exec *exec)
{
  t_jobs	*job;

  job = xmalloc(sizeof(*job));
  job->pgid = pid;
  job->pids = NULL;
  job->status = RUNNING;
  job->cmd = cmd;
  job->background = exec->background;
  job->last = 2;
  job->next = gl_global.gl_jobs;
  job->id = (gl_global.gl_jobs) ? gl_global.gl_jobs->id + 1 : 1;
  if (exec->background == 1 && !exec->parenthesis)
    print_job(job, 1);
 gl_global.gl_jobs = job;
}

void		set_job(int pid, int arg)
{
  t_jobs	*cpy;
  t_jobs	*prev;

  cpy = gl_global.gl_jobs;
  prev = NULL;
  while (cpy && cpy->pgid != pid)
    {
      prev = cpy;
      cpy = cpy->next;
    }
  if (cpy && arg == TERMINATED)
    {
      if (cpy == gl_global.gl_jobs)
	gl_global.gl_jobs = cpy->next;
      else
	prev->next = cpy->next;
      free(cpy->cmd);
      free(cpy);
    }
  else if (cpy && cpy->status != arg)
    {
      cpy->status = arg;
      if (arg == STOPPED)
	print_job(cpy, 0);
    }
}

void		update_pipe(t_lpid *pids, char *cmd)
{
  t_jobs	*cpy;
  char		*to_free;

  cpy = gl_global.gl_jobs;
  if (cpy)
    {
      if (cpy->pids == NULL)
	cpy->pids = pids;
      to_free = cpy->cmd;
      cpy->cmd = my_strcat(NO_FREE, cpy->cmd, " | ", cmd, NULL);
      free(to_free);
    }
  free(cmd);
}

void		del_job(t_lpid *lpid, int bg)
{
  t_jobs	*cpy;
  t_lpid	*next;

  cpy = gl_global.gl_jobs;
  while (cpy && cpy->pids != lpid)
    cpy = cpy->next;
  if (!cpy)
    return ;
  while (lpid && lpid->done)
    lpid = lpid->next;
  if (!lpid)
    {
      lpid = cpy->pids;
      while (lpid)
	{
	  next = lpid->next;
	  free(lpid);
	  lpid = next;
	}
      set_job(cpy->pgid, TERMINATED);
      if (!bg && gl_global.normal_tty)
	xtcsetpgrp(0, getpid());
    }
}
