/*
** bg.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:40:45 2010 cerisier mickael
** Last update Thu May  6 11:35:10 2010 vivien botton
*/

#include <stdlib.h>
#include "parser.h"
#include "jobs.h"
#include "signal.h"
#include "termcaps.h"
#include "gl_vars.h"
#include "execution.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

int			bg(char **cmd)
{
  extern t_global	gl_global;
  t_jobs		*cpy;

  cpy = gl_global.gl_jobs;
  if (cpy && !cmd[1])
    {
      while (cpy->next && cpy->status == RUNNING)
	cpy = cpy->next;
      if (cpy->status == STOPPED)
	update_process(cpy, BACKGROUND);
      else
	return (error_msg("bg : ", "job already in background.\n",
			  EXIT_FAILURE));
      return (EXIT_SUCCESS);
    }
  else if (!cmd[1])
    return (error_msg("bg : ", "No current job.\n", EXIT_FAILURE));
  cpy = get_process(gl_global.gl_jobs, cmd[1]);
  if (cpy && cpy->status != RUNNING)
    update_process(cpy, BACKGROUND);
  else if (cpy && cpy->status == RUNNING)
    return (error_msg("bg : ", "job already in background.\n", EXIT_FAILURE));
  else
    return (error_msg("bg : ", "No such job.\n", EXIT_FAILURE));
  return (EXIT_SUCCESS);
}
