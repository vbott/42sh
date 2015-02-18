/*
** xexecve.c for 42sh in /home/snap/projects/42sh/current
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Fri May 21 11:44:32 2010 botton vivien
** Last update Fri May 21 11:44:32 2010 botton vivien
*/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int	xexecve(const char *filename, char *const argv[],
		   char *const envp[])
{
  int	res;

  res = execve(filename, argv, envp);
  if (res == -1)
    perror("execve");
  return (res);
}
