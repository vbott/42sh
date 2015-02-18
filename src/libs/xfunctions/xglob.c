/*
** xglob.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:40:31 2010 cerisier mickael
** Last update Wed Apr 28 11:40:31 2010 cerisier mickael
*/

#include <glob.h>
#include <stdio.h>

int		xglob(const char *pattern, int flags,
		      int (*errfunc) (const char *epath, int eerrno),
		      glob_t *pglob)
{
  int		i;

  i = glob(pattern, flags, errfunc, pglob);
  if (i != 0 && i != GLOB_NOMATCH)
    perror("glob");
  return (i);
}
