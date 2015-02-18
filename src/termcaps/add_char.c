/*
** add_char.c for 42sh in /u/all/castel_a/cu/svn/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun Mar 21 13:34:05 2010 gianni castellani
** Last update Sat May 22 17:58:14 2010 gianni castellani
*/

#include <stdlib.h>
#include "termcaps.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/strings.h"
#include "lib_includes/aff.h"
#include "gl_vars.h"

extern t_global		gl_global;
extern t_termcap	gl_cap;

void			begin_cursor(size_t i[2])
{
  size_t		end;
  int			cpt;

  end = i[1];
  while (end > i[0])
    {
      if (!((end + gl_global.prompt_len) % gl_cap.co))
	{
	  xtputs(gl_cap.kustr, 1, my_outc);
	  cpt = 0;
	  while (cpt < gl_cap.co - 1)
	    {
	      xtputs(gl_cap.krstr, 1, my_outc);
	      cpt++;
	    }
	}
      else
	xtputs(gl_cap.klstr, 1, my_outc);
      end--;
    }
}

void			add_char(char *buf, char *ch, size_t i[2])
{
  size_t		end;
  size_t		begin;
  size_t		len;

  len = (my_strlen(ch) + i[1] > 4096) ? (4096 - i[1]) : (my_strlen(ch));
  if (ch[0] == '\0' || len == 0)
    return ;
  begin = i[0] + len;
  end = i[1] + len;
  while (--end >= begin)
    buf[end] = buf[end - len];
  begin = len + 1;
  while (--begin >= 1)
    buf[end--] = ch[begin - 1];
  begin = i[0];
  while (begin <= i[1] - 1 + len)
    {
      my_putchar(buf[begin]);
      begin++;
      if (!((begin + gl_global.prompt_len) % gl_cap.co))
	my_putchar('\n');
    }
  i[0] += len;
  i[1] += len;
  begin_cursor(i);
}
