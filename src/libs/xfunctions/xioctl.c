/*
** xioctl.c for 42sh in /u/all/castel_a/cu/svn/current/libs/xfunctions/xfunctions_termcap
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Mar 20 14:41:28 2010 gianni castellani
** Last update Sun Mar 21 16:54:41 2010 gianni castellani
*/

#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>

int		xioctl(int d, unsigned long request, struct termios *term)
{
  int		i;

  i = ioctl(d, request, term);
  if (i == -1)
    {
      perror("ioctl");
      exit(EXIT_FAILURE);
    }
  return (i);
}
