/*
** xopendir.c for  in /u/all/caille_c/cu/42sh/current/libs/xfunctions
** 
** Made by carole cailleux
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr  1 15:23:04 2010 carole cailleux
** Last update Thu Apr  1 15:23:05 2010 carole cailleux
*/

#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>

DIR			*xopendir(const char *name)
{
  DIR			*fd;

  fd = opendir(name);
  if (fd == NULL)
    perror("opendir");
  return (fd);
}
