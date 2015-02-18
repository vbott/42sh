/*
** xclosedir.c for 42sh in /u/all/botton_v/cu/projects/42sh/current/src
** 
** Made by vivien botton
** Login   <botton_v@epitech.net>
** 
** Started on  Sun May 23 22:59:59 2010 vivien botton
** Last update Sun May 23 23:00:06 2010 vivien botton
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int		xclosedir(DIR *dirp)
{
  int		check;

  check = closedir(dirp);
  if (check == -1)
    perror("closedir");
  return (check);
}
