/*
** my_putnstr.c for  in /u/all/caille_c/cu/42sh/current/libs/aff_funcs
** 
** Made by carole cailleux
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr  1 15:20:46 2010 carole cailleux
** Last update Thu Apr  1 15:20:47 2010 carole cailleux
*/

#include <stdlib.h>
#include <unistd.h>
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

void		my_putnstr(const char *str, size_t nb)
{
  size_t	len;

  if (str == NULL)
    return ;
  len = my_strlen(str);
  if (len <= nb)
    xwrite(STDOUT_FILENO, str, len);
  else
    {
      xwrite(STDOUT_FILENO, str, nb);
      xwrite(STDOUT_FILENO, "...", 3);
    }
}
