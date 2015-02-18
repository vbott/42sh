/*
** echo.c for 42sh in /u/all/bereng_p/cu/rendu/SVN/svn/current/builtins
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sat Mar 20 21:56:13 2010 philippe berenguel
** Last update Sat Mar 20 22:12:17 2010 philippe berenguel
*/

#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"
#include "lib_includes/free.h"
#include "lib_includes/xfunctions.h"

static const char	gl_echo[][2] = {
  {'\\', '\\'},
  {'\a', 'a'},
  {'\b', 'b'},
  {'\f', 'f'},
  {'\n', 'n'},
  {'\r', 'r'},
  {'\t', 't'},
  {'\v', 'v'},
  {0, 0}
};

static void	echo_arg(char *arg, int *options, int *i)
{
  int		e;

  options[0] = 0;
  options[1] = 0;
  if (arg == NULL || arg[0] != '-')
    return ;
  e = 1;
  while (arg[e] != '\0')
    {
      if (arg[e] == 'n')
	options[0] = 1;
      else if (arg[e] == 'E')
	options[1] = 0;
      else if (arg[e] == 'e')
	options[1] = 1;
      else
	{
	  options[0] = 0;
	  options[1] = 0;
	  return ;
	}
      e++;
    }
  (*i)++;
}

static void	print_metachar(char *str)
{
  int		i;

  i = 0;
  while (gl_echo[i][0] != 0 && str[1] != gl_echo[i][1])
    i++;
  if (gl_echo[i][0] != 0)
    my_putchar(gl_echo[i][0]);
  else
    xwrite(STDOUT_FILENO, str, 2);
}

int		echo(char **cmd)
{
  int		i;
  int		e;
  int		options[2];

  i = 1;
  e = -1;
  echo_arg(cmd[1], options, &i);
  while (cmd[i])
    {
      if (e != -1)
	my_putchar(' ');
      e = 0;
      while (cmd[i][e] != '\0')
	{
	  if (options[1] == 1 && cmd[i][e] == '\\')
	    print_metachar(&cmd[i][e++]);
	  else
	    my_putchar(cmd[i][e]);
	  e++;
	}
      i++;
    }
  if (options[0] == 0)
    my_putchar('\n');
  return (EXIT_SUCCESS);
}
