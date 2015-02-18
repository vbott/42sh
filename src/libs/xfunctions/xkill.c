/*
** xkill.c for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh/libs/xfunctions
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 13:30:45 2010 philippe berenguel
** Last update Thu May  6 15:40:10 2010 vivien botton
*/

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>

int		xkill(pid_t pid, int sig)
{
  int		i;

  i = kill(pid, sig);
  if (i == -1)
    perror("kill");
  return (i);
}

int		xkillpg(pid_t pgrp, int sig)
{
  int		i;

  i = killpg(pgrp, sig);
  if (i == -1)
    perror("killpg");
  return (i);
}
