/*
** xfork.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/xfunctions
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 11:37:22 2010 philippe berenguel
** Last update Sun Mar 14 11:57:03 2010 philippe berenguel
*/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

pid_t		xfork(void)
{
  pid_t		i;

  i = fork();
  if (i == -1)
    perror("fork");
  return (i);
}
