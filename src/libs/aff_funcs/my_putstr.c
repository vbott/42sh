/*
** my_putstr.c for  in /u/all/caille_c/cu/42sh/current/libs/aff_funcs
** 
** Made by carole cailleux
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr  1 15:20:24 2010 carole cailleux
** Last update Thu Apr  1 15:20:24 2010 carole cailleux
*/

#include <stdlib.h>
#include <unistd.h>
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

void		my_putstr(const char *str)
{
  if (str != NULL)
    xwrite(STDOUT_FILENO, str, my_strlen(str));
}
