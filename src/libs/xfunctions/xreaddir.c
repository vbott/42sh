/*
** xreaddir.c for  in /u/all/caille_c/cu/42sh/current/libs/xfunctions
** 
** Made by carole cailleux
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr  1 15:23:28 2010 carole cailleux
** Last update Thu Apr  1 15:23:29 2010 carole cailleux
*/

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

struct dirent		*xreaddir(DIR *dirp)
{
  struct dirent		*dir;

  dir = readdir(dirp);
  if (dir == NULL && errno == EBADF)
    perror("readdir");
  return (dir);
}
