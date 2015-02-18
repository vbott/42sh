/*
** xsignal.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/xfunctions
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 11:39:18 2010 philippe berenguel
** Last update Sun Mar 14 11:57:28 2010 philippe berenguel
*/

#include <signal.h>
#include <stdio.h>

void		(*xsignal(int signum, void (*handler)(int)))(int)
{
  void		(*i)(int);

  i = signal(signum, handler);
  if (i == SIG_ERR)
    perror("signal");
  return (i);
}
