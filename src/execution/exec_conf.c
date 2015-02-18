/*
** exec_conf.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon May 10 11:23:32 2010 cerisier mickael
** Last update Sat May 22 17:29:39 2010 vivien botton
*/

#include <stdlib.h>
#include "parser.h"
#include "execution.h"
#include "jobs.h"

void		exec_conf(int fd, int job)
{
  char		*str;

  while ((str = get_next_line(fd)))
    {
      if (no_command(str))
	launch_cmd(str, WITHOUT_HIST);
      if (job)
	print_term_jobs(0);
      free(str);
    }
}
