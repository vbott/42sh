/*
** completion.c for 42sh in /u/all/bereng_p/cu/rendu/SVN/42sh/current/ergonomy/completion
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 21 16:48:39 2010 philippe berenguel
** Last update Thu Apr 22 16:28:15 2010 mickael cerisier
*/

#include <stdlib.h>
#include <glob.h>
#include "completion.h"
#include "termcaps.h"
#include "lib_includes/env.h"
#include "lib_includes/aff.h"
#include "lib_includes/free.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

static void	completion_frees(t_info *info, char *exp)
{
  free(info->to_match);
  free(exp);
  if (info->mode > 2)
    {
      free(info->to_free);
      if (info->path)
	free(info->path);
    }
}

static int	check_case(char *to_match, int mode)
{
  int		c;
  int		p;

  c = mode;
  p = 0;
  if (to_match != NULL)
    {
      while (to_match[p] != '\0' && to_match[p] != '/')
	p++;
      if (to_match[p] == '/')
	c = 0;
      else if (to_match[0] == '.')
	c = 0;
     }
  return (c);
}

static void	secondary_cases(char *exp, glob_t *globr, int mode)
{
  char		*to_match;

  if (mode == 0)
    xglob(exp, GLOB_TILDE | GLOB_MARK, NULL, globr);
  else if (mode == 1)
    xglob("./*",  GLOB_TILDE | GLOB_MARK, NULL, globr);
  else if (mode == 2)
    {
      to_match = my_strcat(NO_FREE, "./", exp, NULL);
      xglob(to_match, GLOB_TILDE | GLOB_MARK, NULL, globr);
      free(to_match);
    }
}

static void	searches(t_info *info, glob_t *globr)
{
  int		p;
  char		*to_match;

  if (info->mode > 2)
    {
      p = 0;
      while (info->path && info->path[p])
	{
	  if (info->to_match != NULL)
	    to_match = my_strcat(FIRST_FREE,
				 my_strcat(NO_FREE, info->path[p], "/", NULL),
				 info->to_match, NULL);
	  else
	    to_match = my_strcat(NO_FREE, info->path[p], "/*", NULL);
	  if (p > 0)
	    xglob(to_match, GLOB_TILDE | GLOB_MARK | GLOB_APPEND, NULL, globr);
	  else
	    xglob(to_match, GLOB_TILDE | GLOB_MARK, NULL, globr);
	  p++;
	  free(to_match);
	}
    }
  else
    secondary_cases(info->to_match, globr, info->mode);
}

void		completion(char *buffer, size_t curs[2])
{
  char		*exp;
  glob_t	globres;
  t_info	info;

  info.mode = 3;
  info.path = NULL;
  buffer[curs[1]] = '\0';
  exp = my_strndup(buffer, curs[0]);
  info.to_match = parsing(exp, &info.mode);
  if ((info.mode = check_case(info.to_match, info.mode)) > 2)
    {
      info.to_free = my_strdup(my_getenv("PATH"));
      info.path = my_explode(info.to_free, ':');
    }
  if (info.to_match == NULL && info.mode < 3)
    info.to_match = my_strcat(NO_FREE, "*", NULL);
  else if (info.to_match != NULL)
    info.to_match = my_strcat(FIRST_FREE, info.to_match, "*", NULL);
  if (info.mode <= 2 || info.path != NULL)
    {
      searches(&info, &globres);
      aff(globres.gl_pathv, buffer, curs, &info);
      globfree(&globres);
    }
  completion_frees(&info, exp);
}
