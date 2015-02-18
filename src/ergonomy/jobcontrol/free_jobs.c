/*
** free_jobs.c for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 14:48:07 2010 philippe berenguel
** Last update Fri Apr  2 14:48:08 2010 philippe berenguel
*/

#include <stdlib.h>
#include <signal.h>
#include "parser.h"
#include "jobs.h"
#include "lib_includes/xfunctions.h"

void		free_jobs(t_jobs *progs)
{
  t_jobs	*cpy;

  while (progs)
    {
      cpy = progs;
      progs = progs->next;
      xkillpg(cpy->pgid, SIGTERM);
      free(cpy->cmd);
      free(cpy);
    }
}
