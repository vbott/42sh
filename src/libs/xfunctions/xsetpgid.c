/*
** xtcsetpgrp.c for 42sh in /home/snap/projects/42sh/current/src/libs/xfunctions
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Thu May  6 14:47:16 2010 botton vivien
** Last update Thu May  6 14:47:16 2010 botton vivien
*/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int		xsetpgid(int pid, int pgid)
{
  int		i;

  i = setpgid(pid, pgid);
  if (i == -1)
    perror("setpgid");
  return (i);
}
