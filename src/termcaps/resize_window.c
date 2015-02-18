/*
** resize_window.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Wed May 19 17:04:00 2010 gianni castellani
** Last update Sat May 22 17:56:28 2010 gianni castellani
*/

#include "gl_vars.h"
#include "lib_includes/xfunctions.h"
#include "ergonomy.h"
#include "lib_includes/aff.h"

extern t_termcap	gl_cap;

static void		move_begin_cursor(size_t curs_pos[2])
{
  size_t		cpt;

  cpt = 0;
  while (cpt < curs_pos[0])
    {
      xtputs(gl_cap.klstr, 1, my_outc);
      cpt++;
    }
  cpt = 0;
  while (cpt < curs_pos[1])
    {
      xtputs(gl_cap.cestr, 1, my_outc);
      xtputs(gl_cap.kustr, 1, my_outc);
      cpt++;
    }
  xtputs(gl_cap.cestr, 1, my_outc);
}

void			fill_curs_pos(size_t curs_pos[2], int i,
				      size_t old, size_t new)
{
  extern t_global	gl_global;

  curs_pos[0] = (gl_global.curs_pos[i] + gl_global.prompt_len) % old;
  curs_pos[1] = (gl_global.curs_pos[i] + gl_global.prompt_len) / old;
  if (curs_pos[0] > new)
    curs_pos[0] = new;
}

void			move_cursor_at_cursor(size_t curs_pos[2],
					      size_t curs_posend[2])
{
  size_t		cpt;

  cpt = 0;
  if (curs_posend[0] < curs_pos[0])
    while (cpt + curs_posend[0] < curs_pos[0])
      {
	xtputs(gl_cap.klstr, 1, my_outc);
	cpt++;
      }
  else
    while (cpt + curs_pos[0] < curs_posend[0])
      {
	xtputs(gl_cap.krstr, 1, my_outc);
	cpt++;
      }
  cpt = 0;
  while (cpt < curs_posend[1] - curs_pos[1])
    {
      xtputs(gl_cap.kdstr, 1, my_outc);
      cpt++;
    }
}

void			resize_window(size_t old, size_t new)
{
  extern t_global	gl_global;
  size_t		curs_pos[2];
  size_t		curs_posend[2];
  size_t		cpt;

  curs_pos[0] = 0;
  curs_pos[1] = 0;
  if (gl_global.curs_pos)
    {
      fill_curs_pos(curs_pos, 0, old, new);
      fill_curs_pos(curs_posend, 1, old, new);
    }
  move_cursor_at_cursor(curs_pos, curs_posend);
  move_begin_cursor(curs_posend);
  aff_prompt();
  cpt = 0;
  while (cpt < gl_global.curs_pos[1])
    {
      my_putchar(gl_global.buffer[cpt]);
      cpt++;
      if (!((cpt + gl_global.prompt_len) % gl_cap.co))
	my_putchar('\n');
    }
  begin_cursor(gl_global.curs_pos);
}
