/*
** termcap.c for 42sh in /u/all/castel_a/cu/svn/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Mar 20 11:06:29 2010 gianni castellani
** Last update Sun May 23 19:04:35 2010 gianni castellani
*/

#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <term.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "builtins.h"
#include "ergonomy.h"
#include "execution.h"
#include "gl_vars.h"
#include "history.h"

extern t_global		gl_global;

void			begin_buff(char *buf, size_t i[2])
{
  gl_global.buffer = buf;
  gl_global.curs_pos = i;
  i[0] = 0;
  i[1] = 0;
  while (buf[i[0]] != '\0')
    {
      my_putchar(buf[i[0]]);
      i[0]++;
      i[1]++;
    }
  buf[i[1]] = '\0';
}

static void		exec_bind(char *buf, size_t i[2], char *command)
{
  char			*str;

  str = my_strdup(command);
  my_putchar('\n');
  if (no_command(str))
    {
      if (!my_strcmp(command, "exit"))
	{
	  while (gl_global.history->prev)
	    gl_global.history = gl_global.history->prev;
	  gl_global.history = gl_global.history->next;
	  free(gl_global.history->prev->data);
	  free(gl_global.history->prev);
	  gl_global.history->prev = NULL;
	}
      launch_cmd(str, WITHOUT_HIST);
    }
  free(str);
  aff_prompt();
  xwrite(STDOUT_FILENO, buf, i[1]);
  begin_cursor(i);
}

void			handle_char(char *ch, char *buf, size_t i[2],
				    t_bindkey *current)
{
  if (current != NULL && current->exec)
    exec_bind(buf, i, current->exec);
  else if (current != NULL)
    current->function(buf, i);
  else if (ch[0] >= 32 && ch[0] < 127)
    add_char(buf, ch, i);
  else
    add_char(buf, "~", i);
}

void			read_char(char *ch, int *nb_read)
{
  int			cpt;

  *nb_read = xread(STDIN_FILENO, ch, 4095);
  if (*nb_read != -1)
    {
      if (*nb_read > 0 && ch[0] == ASC_ENTER)
	ch[1] = '\0';
      else
	{
	  ch[*nb_read] = '\0';
	  if (*nb_read != 1 || ch[0] != ASC_ENTER)
	    {
	      cpt = 0;
	      while (cpt < *nb_read && ch[cpt] != ASC_ENTER)
		cpt++;
	      ch[cpt] = '\0';
	    }
	}
    }
}

void			my_read(char *buf)
{
  size_t	i[2];
  char		ch[4096];
  int		nb_read;
  t_bindkey	*current;

  begin_buff(buf, i);
  create_commandnode();
  read_char(ch, &nb_read);
  while ((nb_read != -1 || errno == EINTR) &&
	 (ch[0] != ASC_ENTER || ch[1] != '\0'))
    {
      current = gl_global.gl_bindkey;
      while (current != NULL
	     && !my_strncmp(current->ch, ch, my_strlen(current->ch)))
	current = current->next;
      handle_char(ch, buf, i, current);
      read_char(ch, &nb_read);
    }
  my_cursor_end(buf, i);
  delete_commandnode();
  my_putstr("\n");
  buf[i[1]] = '\0';
}
