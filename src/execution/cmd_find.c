/*
** cmd_find.c for 42sh in /u/all/bereng_p/cu/rendu/SVN/svn/current/execution
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 21 12:28:43 2010 philippe berenguel
** Last update Sun May 23 20:54:08 2010 vivien botton
*/

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "parser.h"
#include "execution.h"
#include "lib_includes/free.h"
#include "lib_includes/aff.h"
#include "lib_includes/env.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/strings.h"
#include "builtins.h"
#include "jobs.h"
#include "termcaps.h"
#include "gl_vars.h"

static int	exec_cmd(char *cmd, char **args,
			 t_exec *exec, t_lpid *lpid)
{
  int		status;
  pid_t		father;

  status = EXIT_SUCCESS;
  father = xfork();
  if (father == -1)
    return (-1);
  if (father)
    {
      close_fd(exec->fd);
      if (!exec->background && (!exec->pipe || !lpid))
	add_job(father, my_implode(args), exec);
      else if (!exec->background)
	update_pipe(lpid, my_implode(args));
      if (exec->pipe)
	return (father);
      handle_status(father, &status, !exec->background, exec->background);
    }
  else
    {
      exec_child(cmd, args, exec, lpid);
      exit(EXIT_FAILURE);
    }
  return (status);
}

static int	is_valid(char *cmd)
{
  struct stat	dir;

  if (xstat(cmd, &dir) != -1)
    {
      if (!S_ISDIR(dir.st_mode))
	return (1);
      else
	{
	  my_puterror(cmd);
	  my_puterror(" : is a directory.\n");
	}
    }
  return (0);
}

static int	cmd_in_path(char **args, t_exec *exec, t_lpid *lpid)
{
  char		**path_dir;
  char		*cmd;
  char		*path;
  int		i;

  path = my_strdup(my_getenv("PATH"));
  if ((path_dir = my_explode(path, ':')) == NULL)
    return (-1);
  i = -1;
  while (path_dir[++i] != NULL)
    {
      cmd = my_strcat(NO_FREE, path_dir[i], "/", args[0], NULL);
      if (cmd != NULL && !access(cmd, X_OK))
	{
	  i = exec_cmd(cmd, args, exec, lpid);
	  free(path);
	  free(cmd);
	  free(path_dir);
	  return (i);
	}
      free(cmd);
    }
  free(path);
  free(path_dir);
  return (-1);
}

static int	binary_find(char **cmd, t_exec *exec,
			    t_lpid *lpid, int *found)
{
  int		res;

  if (!my_strcmp(cmd[0], ".") || !my_strcmp(cmd[0], ".."))
    {
      *found = 1;
      return (error_msg(cmd[0], " : is a directory.\n", 0));
    }
  else if (char_find(cmd[0], '/') != -1 && !access(cmd[0], F_OK))
    {
      *found = 1;
      if (!access(cmd[0], X_OK))
	{
	  if (is_valid(cmd[0]))
	    return (exec_cmd(cmd[0], cmd, exec, lpid));
	}
      else
	return (error_msg(cmd[0], " : Permission denied.\n", 0));
    }
  else if ((res = cmd_in_path(cmd, exec, lpid)) != -1)
    {
      *found = 1;
      return (res);
    }
  return (-1);
}

int		cmd_find(char **cmd, t_exec *exec, t_lpid *lpid)
{
  int		res;
  int		found;

  found = 0;
  res = EXIT_FAILURE;
  if (cmd != NULL)
    {
      if (cmd[0] && cmd[0][0])
	{
	  res = builtin_find(cmd, exec, lpid, &found);
	  if (!found)
	    res = binary_find(cmd, exec, lpid, &found);
	}
      if (!found)
	{
	  close_fd(exec->fd);
	  my_puterror(cmd[0]);
	  my_puterror(" : Command not found.\n");
	  if (exec->pipe)
	    res = exec_cmd(NULL, cmd, exec, lpid);
	}
    }
  usleep(1);
  return ((found || exec->pipe) ? res : EXIT_FAILURE);
}
