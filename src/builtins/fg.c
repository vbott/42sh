/*
** fg.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:42:48 2010 cerisier mickael
** Last update Thu May 13 18:35:37 2010 gianni castellani
*/

#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "parser.h"
#include "jobs.h"
#include "execution.h"
#include "termcaps.h"
#include "gl_vars.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

extern t_global	gl_global;

void			change_last(int change, int pgid)
{
  t_jobs		*jobs;

  jobs = gl_global.gl_jobs;
  while	(jobs)
    {
      if (jobs->pgid != pgid && jobs->last + change < 3)
	jobs->last += change;
      jobs = jobs->next;
    }
}

int			update_process(t_jobs *cpy, int background)
{
  int			status;
  int			last;
  int			pgid;

  status = EXIT_SUCCESS;
  my_putnstr(cpy->cmd, MAX_LEN_CMD);
  my_putstr("\n");
  pgid = cpy->pgid;
  cpy->status = RUNNING;
  cpy->background = background;
  last = cpy->last;
  cpy->last = 2;
  if (!background && gl_global.normal_tty)
    xtcsetpgrp(0, cpy->pgid);
  if (xkillpg(cpy->pgid, SIGCONT) != -1 && !background)
    {
      if (!cpy->pids)
	handle_status(cpy->pgid, &status, 1, 0);
      else
	status = handle_wait_pipe(cpy->pids, 0);
      if ((last == 2 && WIFSTOPPED(status)) ||
			WIFEXITED(status) || WIFSIGNALED(status))
	change_last(1, pgid);
    }
  return (status);
}

t_jobs			*get_process(t_jobs *jobs, const char *arg)
{
  int			id;

  if (!my_strcmp(arg, "+"))
    {
      while (jobs && jobs->last != 2)
	jobs = jobs->next;
    }
  else if (!my_strcmp(arg, "-"))
    {
      while (jobs && jobs->last != 1)
	jobs = jobs->next;
    }
  else
    {
      id = my_atoi(arg);
      while (jobs && jobs->id != id)
	jobs = jobs->next;
    }
  return (jobs);
}

int			fg(char **cmd)
{
  t_jobs		*cpy;

  if (gl_global.gl_jobs && !cmd[1])
    {
      cpy = get_process(gl_global.gl_jobs, "+");
      if (!cpy)
	return (EXIT_FAILURE);
      return (update_process(cpy, FOREGROUND));
    }
  else if (!cmd[1])
    return (error_msg("fg : ", "No current job.\n", EXIT_FAILURE));
  cpy = get_process(gl_global.gl_jobs, cmd[1]);
  if (cpy)
    return (update_process(cpy, FOREGROUND));
  else
    return (error_msg("fg : ", "No such job.\n", EXIT_FAILURE));
  return (EXIT_FAILURE);
}
