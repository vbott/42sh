/*
** jobs.c for 42sh in /home/snap/projects/42sh/current
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Fri May 14 15:25:15 2010 botton vivien
** Last update Fri May 14 15:25:15 2010 botton vivien
*/

#include <stdlib.h>
#include "parser.h"
#include "execution.h"
#include "jobs.h"
#include "termcaps.h"
#include "gl_vars.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"

extern t_global	gl_global;

void		print_job(t_jobs *job, int showpid)
{
  my_putchar('[');
  my_putnbr(job->id);
  my_putchar(']');
  if (job->last == 2)
    my_putchar('+');
  else if (job->last == 1)
    my_putchar('-');
  else
    my_putchar(' ');
  my_putchar(' ');
  if (showpid)
    my_putnbr(job->pgid);
  else if (job->status == STOPPED)
    my_putstr("Stopped");
  else if (job->status == RUNNING)
    my_putstr("Running");
  else
    my_putstr(get_signal(job->status));
  my_putchar('\t');
  my_putnstr(job->cmd, MAX_LEN_CMD);
  my_putchar('\n');
}

void		reverse_print(t_jobs *jobs, int mode, int showpid)
{
  if (jobs->next)
    reverse_print(jobs->next, mode, showpid);
  if (mode == NORMAL_PRINT || (mode & PRINT_RUNNING && jobs->status == RUNNING)
      || (mode & PRINT_STOPPED && jobs->status == STOPPED))
    print_job(jobs, showpid);
}

void		jobs_usage(void)
{
  my_puterror("jobs: usage: jobs [-prs] [jobspec ...]\n");
}

void		handle_params(char **cmd, int *mode)
{
  int		i;
  int		j;

  i = 0;
  while (cmd[++i] && *mode != -1)
    if (cmd[i][0] == '-')
      {
	j = 1;
	while (cmd[i][j] && *mode != -1)
	  {
	    if (cmd[i][j] == 'p')
	      *mode |= PRINT_PID;
	    else if (cmd[i][j] == 'r')
	      *mode |= PRINT_RUNNING;
	    else if (cmd[i][j] == 's')
	      *mode |= PRINT_STOPPED;
	    else
	      *mode = -1;
	    j++;
	  }
      }
  if (*mode == -1)
    jobs_usage();
}

int		jobs(char **cmd)
{
  int		i;
  t_jobs	*cpy;
  int		mode;

  mode = NORMAL_PRINT;
  handle_params(cmd, &mode);
  if (mode == -1)
    return (EXIT_FAILURE);
  cpy = gl_global.gl_jobs;
  i = 1;
  if ((!cmd[1] || (mode != NORMAL_PRINT && !cmd[2])) && cpy)
    reverse_print(cpy, mode & ~PRINT_PID, mode & PRINT_PID);
  else
    while (cmd[i])
      {
	cpy = gl_global.gl_jobs;
	while (cpy)
	  {
	    if (my_atoi(cmd[i]) == cpy->id)
	      print_job(cpy, mode & PRINT_PID);
	    cpy = cpy->next;
	  }
	i++;
      }
  return (EXIT_SUCCESS);
}
