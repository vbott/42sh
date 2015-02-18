/*
** xgetcwd.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon May 17 13:43:42 2010 cerisier mickael
** Last update Mon May 17 13:43:42 2010 cerisier mickael
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char		*xgetcwd(char *buf, size_t size)
{
  char		*mem;

  mem = getcwd(buf, size);
  if (mem == NULL)
    perror("getcwd");
  return (mem);
}
