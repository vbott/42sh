/*
** my_cursorhome.c for 42sh in /u/all/castel_a/cu/42sh/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 11:39:49 2010 gianni castellani
** Last update Wed May 19 16:20:18 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/xfunctions.h"
#include "termcaps.h"

void			my_cursor_home(__attribute__((unused))
				       char *buf, size_t i[2])
{
  size_t		j[2];

  j[0] = 0;
  j[1] = i[0];
  begin_cursor(j);
  i[0] = 0;
}
