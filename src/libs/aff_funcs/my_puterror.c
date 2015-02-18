/*
** my_puterror.c for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh/libs/free_funcs
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 13:37:15 2010 philippe berenguel
** Last update Fri Apr  2 13:37:16 2010 philippe berenguel
*/

#include <unistd.h>
#include <stdlib.h>
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

void		my_puterror(const char *str)
{
  if (str != NULL)
    xwrite(STDERR_FILENO, str, my_strlen(str));
}
