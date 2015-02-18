/*
** xtputs.c for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh/libs/xfunctions
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 13:32:32 2010 philippe berenguel
** Last update Fri Apr  2 13:32:33 2010 philippe berenguel
*/

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <stdio.h>

int		xtputs(const char *str, int affcnt, int (*putc)(int))
{
  int		i;

  i = tputs(str, affcnt, putc);
  if (i == ERR)
    {
      perror("tputs");
      exit(EXIT_FAILURE);
    }
  return (i);
}
