/*
** xtgetstr.c for 42sh in /u/all/castel_a/cu/svn/current/libs/xfunctions/xfunctions_termcap
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Mar 20 11:37:07 2010 gianni castellani
** Last update Sun Mar 21 16:54:26 2010 gianni castellani
*/

#include <ncurses.h>
#include <stdlib.h>
#include <term.h>
#include <stdio.h>

char		*xtgetstr(char *id, char **area)
{
  char		*i;

  i = tgetstr(id, area);
  if (i == NULL)
    perror("tgetstr");
  return (i);
}
