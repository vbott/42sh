/*
** bind_key.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Fri Apr  2 13:52:30 2010 gianni castellani
** Last update Mon May  3 14:47:21 2010 gianni castellani
*/

#include <stdlib.h>
#include <sys/ioctl.h>
#include "lib_includes/strings.h"
#include "lib_includes/aff.h"
#include "lib_includes/xfunctions.h"
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"
#include "lib_includes/free.h"

void			bk_create_maillon(t_bindkey *prev, t_bindkey *current,
					  char *str, char *str2)
{
  t_bindkey		*new;

  new = xmalloc(sizeof(*new));
  new->ch = my_strdup(str);
  new->exec = my_strdup(str2);
  new->next = (current) ? (current->next) : (0);
  prev->next = new;
  free(current);
}

void			bk_handlecreate(char *str, char *str2)
{
  extern t_global	gl_global;
  t_bindkey		*current;
  t_bindkey		*prev;

  current = gl_global.gl_bindkey;
  prev = gl_global.gl_bindkey;
  while (current && my_strcmp(str, current->ch))
    {
      prev = current;
      current = current->next;
    }
  if (current == gl_global.gl_bindkey)
    {
      gl_global.gl_bindkey = xmalloc(sizeof(*gl_global.gl_bindkey));
      gl_global.gl_bindkey->ch = my_strdup(str);
      gl_global.gl_bindkey->exec = my_strdup(str2);
      gl_global.gl_bindkey->next = current->next;
      free(current);
    }
  else
    bk_create_maillon(prev, current, str, str2);
}

void			bk_handleinteract(char *command)
{
  int			nb_read;
  char			buf[10];
  t_termios		new;
  t_termios		old;

  my_putstr("Insert char: ");
  no_canonic_mode(&new, &old, NULL);
  xioctl(0, TIOCSETA, &new);
  nb_read = xread(STDIN_FILENO, buf, 10);
  buf[nb_read] = '\0';
  my_putstr("OK\n");
  bk_handlecreate(buf, command);
  xioctl(0, TIOCSETA, &old);
}

int			bind_key(char **cmd)
{
  if (cmd[1] != NULL && cmd[2] != NULL && !my_strcmp(cmd[1], "-d"))
    bk_handledelete(cmd[2]);
  else if (cmd[1] != NULL && cmd[2] != NULL
	   && cmd[3] != NULL && !my_strcmp(cmd[1], "-c"))
    bk_handlecreate(cmd[2], cmd[3]);
  else if (cmd[1] != NULL && cmd[2] != NULL && !my_strcmp(cmd[1], "-i"))
    bk_handleinteract(cmd[2]);
  else
    {
      my_puterror("Usage: bindkey [options] [char] [command]\n");
      my_puterror("Options: -c: Interpret command.\n");
      my_puterror("\t -d: Delete bind.\n\t -i: Interactive bind.\n");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
