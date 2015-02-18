/*
** env_arg.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Fri May 14 15:24:45 2010 cerisier mickael
** Last update Fri May 14 15:24:45 2010 cerisier mickael
*/

#include <stdlib.h>
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

static void		aff_help_env(void)
{
  my_puterror("Usage: env [OPTION] [COMMAND [ARG]...]\nSet each ");
  my_puterror("NAME to VALUE in the environment and run COMMAND.\n\n");
  my_puterror("   -i, --ignore-environment\tstart with an empty environment");
  my_puterror("\n   --help\t\t\tdisplay this help and exit\n");
}

static int		handle_error_arg(int i, char **cmd, int *option)
{
  int			e;

  e = 1;
  while (cmd[i][e] != '\0')
    {
      if (cmd[i][e] == 'i')
	option[0] = 1;
      else
	{
	  my_puterror("env: invalid option -- '");
	  xwrite(STDERR_FILENO, &cmd[i][e], 1);
	  my_puterror("'\nTry `env --help' for more information.\n");
	  return (-1);
	}
      e++;
    }
  return (0);
}

static int		handle_error_arg2(int i, char **cmd, int *option)
{
  if (!my_strcmp(cmd[i], "--ignore-environment"))
    option[0] = 1;
  else if (!my_strcmp(cmd[i], "--help"))
    aff_help_env();
  else
    {
      my_puterror("env: unrecognized option '");
      my_puterror(cmd[i]);
      my_puterror("'\nTry `env --help' for more information.\n");
      return (-1);
    }
  return (0);
}

int			argument_parser(char **cmd, int *option)
{
  int			i;

  i = 1;
  while (cmd[i] != NULL)
    {
      if (cmd[i][0] == '-' && cmd[i][1] == '-')
	{
	  if ((handle_error_arg2(i, cmd, option)) == -1)
	    return (-1);
	}
      else if (cmd[i][0] == '-')
	{
	  if ((handle_error_arg(i, cmd, option)) == -1)
	    return (-1);
	}
      else
	return (i);
      i++;
    }
  return (-1);
}
