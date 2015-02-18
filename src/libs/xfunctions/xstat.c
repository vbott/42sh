/*
** xstat.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Sun May 23 15:37:00 2010 cerisier mickael
** Last update Sun May 23 15:37:00 2010 cerisier mickael
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int		xstat(const char *path, struct stat *buf)
{
  int		check;

  check = stat(path, buf);
  if (check == -1)
    perror("stat");
  return (check);
}
