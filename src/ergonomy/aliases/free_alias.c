/*
** free_alias.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed May 19 19:13:31 2010 cerisier mickael
** Last update Wed May 19 19:13:31 2010 cerisier mickael
*/

#include <stdlib.h>
#include "parser.h"
#include "builtins.h"
#include "lib_includes/strings.h"
#include "gl_vars.h"

extern t_global	gl_global;

void		free_alias(void)
{
  t_alias	*savenext;

  while (gl_global.gl_alias)
    {
      savenext = gl_global.gl_alias->next;
      free(gl_global.gl_alias->assign);
      free(gl_global.gl_alias->value);
      free(gl_global.gl_alias);
      gl_global.gl_alias = savenext;
    }
}
