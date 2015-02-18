/*
** prompt.c for  in /u/all/caille_c/cu/42sh/current/ergonomy/interface
** 
** Made by carole cailleux
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr  1 15:17:15 2010 carole cailleux
** Last update Fri May 21 12:50:20 2010 gianni castellani
*/

#include <lib_includes/env.h>
#include <lib_includes/aff.h>
#include <lib_includes/strings.h>
#include "gl_vars.h"

extern char		**env;
extern t_global		gl_global;
extern t_termcap	gl_cap;

int			cut_pwd(char *str)
{
  char			*home;
  int			len_home;

  home = my_getenv("HOME");
  len_home = my_strlen(home);
  if (len_home != 0 && my_strncmp(str, home, len_home))
    {
      my_putchar('~');
      my_putstr(&str[len_home]);
      return (1 + my_strlen(&str[len_home]));
    }
  my_putstr(str);
  return (my_strlen(str));
}

void			aff_prompt(void)
{
  char			*data;

  gl_global.prompt_len = 2;
  if ((data = my_getenv("USER")))
    {
      my_putstr("\033[01;32m");
      my_putstr(data);
      my_putstr("\033[00m");
      gl_global.prompt_len += my_strlen(data);
    }
  my_putchar(':');
  gl_global.prompt_len++;
  if ((data = my_getenv("PWD")))
    {
      my_putstr("\033[01;34m");
      gl_global.prompt_len += cut_pwd(data);
      my_putstr("\033[00m");
    }
  my_putstr("$");
  if (!((gl_global.prompt_len - 1) % gl_cap.co))
    my_putchar('\n');
  my_putstr(" ");
  if (!((gl_global.prompt_len) % gl_cap.co))
    my_putchar('\n');
}
