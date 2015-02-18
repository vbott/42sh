/*
** my_putchar.c for  in /u/all/caille_c/cu/42sh/current/libs/aff_funcs
** 
** Made by carole cailleux
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr  1 15:20:09 2010 carole cailleux
** Last update Thu Apr  1 15:20:10 2010 carole cailleux
*/

#include <unistd.h>
#include "lib_includes/aff.h"
#include "lib_includes/xfunctions.h"

void		my_putchar(const char c)
{
  xwrite(STDOUT_FILENO, &c, 1);
}
