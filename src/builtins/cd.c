/*
** cd.c for 42sh in /u/all/bereng_p/cu/rendu/SVN/svn/current/builtins
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sat Mar 20 22:05:14 2010 philippe berenguel
** Last update Thu May 13 18:36:51 2010 gianni castellani
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "parser.h"
#include "builtins.h"
#include "termcaps.h"
#include "execution.h"
#include "jobs.h"
#include "gl_vars.h"
#include "lib_includes/strings.h"
#include "lib_includes/env.h"
#include "lib_includes/aff.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/free.h"

static char		*deconcat_path(char *path_tmp)
{
  int			len;

  if (!path_tmp || !my_strcmp("/", path_tmp))
    return (path_tmp);
  len = my_strlen(path_tmp);
  while (len > 0 && path_tmp[len] != '/')
    len--;
  if (len > 0)
    path_tmp[len] = '\0';
  else
    {
      free(path_tmp);
      path_tmp = my_strdup("/");
    }
  return (path_tmp);
}

char			*find_tmp_path(char *cmd)
{
  char			**path_tab;
  int			i;
  char			*res;

  i = 0;
  if (cmd[0] == '/')
    res = my_strdup("/");
  else if ((res = my_getenv("PWD")))
    res = my_strdup(res);
  else
    return (getcwd(NULL, 0));
  path_tab = my_explode(cmd, '/');
  while (path_tab[i])
    {
      if (!my_strcmp("..", path_tab[i]))
	res = deconcat_path(res);
      else if (!my_strcmp(res, "/") && my_strcmp(path_tab[i], "."))
	res = my_strcat(FIRST_FREE, res, path_tab[i], 0);
      else if (my_strcmp(path_tab[i], "."))
	res = my_strcat(FIRST_FREE, res, "/", path_tab[i], 0);
      i++;
    }
  free(cmd);
  free(path_tab);
  return (res);
}

static void		modify_pwd(char *path_tmp)
{
  int			i;
  char			*tab[4];
  extern t_global	gl_global;

  i = 0;
  while (gl_global.gl_env[i] && !my_strccmp("PWD", gl_global.gl_env[i], '='))
    i++;
  if (gl_global.gl_env[i])
    {
      free(gl_global.gl_env[i]);
      gl_global.gl_env[i] = my_strcat(0, "PWD", "=", path_tmp, 0);
    }
  else
    {
      tab[0] = "setenv";
      tab[1] = "PWD";
      tab[2] = path_tmp;
      tab[3] = NULL;
      my_setenv(tab);
    }
}

void			modify_oldpwd(void)
{
  char			*oldpwd[4];

  oldpwd[0] = "setenv";
  oldpwd[1] = "OLDPWD";
  oldpwd[2] = my_getenv("PWD");
  oldpwd[3] = NULL;
  my_setenv(oldpwd);
}

int			cd(char **cmd)
{
  char			*path_tmp;
  int			len;

  len = len_tab(cmd);
  if (len > 2)
    return (error_msg("cd: ", "Too many arguments.\n", EXIT_FAILURE));
  if (len == 1)
    path_tmp = my_strdup(my_getenv("HOME"));
  else if (!my_strcmp(cmd[1], "-"))
    path_tmp = my_strdup(my_getenv("OLDPWD"));
  else
    path_tmp = my_strdup(cmd[1]);
  if (!path_tmp || xchdir(path_tmp) == -1)
    {
      if (path_tmp)
	free(path_tmp);
      return (EXIT_FAILURE);
    }
  path_tmp = find_tmp_path(path_tmp);
  modify_oldpwd();
  modify_pwd(path_tmp);
  if (path_tmp)
    free(path_tmp);
  return (EXIT_SUCCESS);
}
