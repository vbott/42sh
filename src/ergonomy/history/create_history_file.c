/*
** create_history_file.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun May  9 17:46:21 2010 gianni castellani
** Last update Wed May 12 10:17:44 2010 gianni castellani
*/

#include <stdlib.h>
#include <sys/stat.h>
#include "termcaps.h"
#include "parser.h"
#include "history.h"
#include "jobs.h"
#include "gl_vars.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

extern t_global	gl_global;

void		create_history_file(void)
{
  int		fd;
  t_history	*hist;
  char		*file;

  file = my_getlocal("HISTFILE");
  if (!file)
    return ;
  fd = xopen(file, O_TRUNC | O_RDWR | O_CREAT,
	     S_IRUSR | S_IWUSR | S_IRGRP | S_IRWXO);
  if (fd == -1)
    return ;
  while (gl_global.history->next)
    gl_global.history = gl_global.history->next;
  while (gl_global.history != NULL)
    {
      xwrite(fd, gl_global.history->data, my_strlen(gl_global.history->data));
      xwrite(fd, "\n", 1);
      free(gl_global.history->data);
      hist = gl_global.history;
      gl_global.history = gl_global.history->prev;
      free(hist);
    }
  xclose(fd);
}
