/*
** my_strcat.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/string_funcs
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 11:22:32 2010 philippe berenguel
** Last update Wed Apr 28 11:39:39 2010 cerisier mickael
*/

#include <stdlib.h>
#include <stdarg.h>
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

/* my_strcat :
   This function takes as parameters a mode (NO_FREE, FIRST_FREE,
   or ALL_FREE) and an infinite number of character strings.
   The last string from the list has to be NULL.
   The NO_FREE mode takes no parameter.
   The FIRST_FREE mode only frees the first argument from the list.
   The ALL_FREE mode frees all arguments from the list.

   NO_FREE = 0
   FIRST_FREE = 1
   ALL_FREE = 2
*/

static int	len_strcat(va_list *ap)
{
  char		*str;
  int		len;

  len = 0;
  while ((str = va_arg(*ap, char *)))
    len += my_strlen(str);
  return (len);
}

char		*my_strcat(int mode, ...)
{
  va_list	ap;
  char		*str;
  char		*res;
  int		i;
  int		j;

  j = 0;
  va_start(ap, mode);
  res = xmalloc(sizeof(*res) * (len_strcat(&ap) + 1));
  va_end(ap);
  va_start(ap, mode);
  while ((str = va_arg(ap, char *)))
    {
      i = 0;
      while (str[i])
	res[j++] = str[i++];
      if ((mode == FIRST_FREE && j == i) || mode == ALL_FREE)
	free(str);
    }
  res[j] = '\0';
  va_end(ap);
  return (res);
}
