/*
** xwaitpid.c for  in /u/all/caille_c/cu/42sh/current/libs/xfunctions
** 
** Made by carole cailleux
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr  1 15:23:16 2010 carole cailleux
** Last update Fri May 21 17:16:35 2010 vivien botton
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

pid_t		xwaitpid(pid_t pid, int *status, int options)
{
  pid_t		endpid;

  endpid = waitpid(pid, status, options);
  if (endpid == -1)
    perror("waitpid");
  return (endpid);
}
