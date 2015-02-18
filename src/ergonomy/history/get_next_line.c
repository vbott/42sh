/*
** get_next_line.c for get_next_line in /u/all/cerisi_m/cu/rendu/c/get_next_line
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Thu Nov 12 10:16:01 2009 mickael cerisier
** Last update Mon May 10 15:15:35 2010 gianni castellani
*/

#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "history.h"
#include "lib_includes/xfunctions.h"

int		strlen_gnl(char *str)
{
  int		i;

  if (str == 0)
    return (0);
  i = 0;
  while (str[i] != '\n' && str[i] != '\0')
    i++;
  return (i);
}

char		*strconcate_gnl(char *str, char *buffer, int size)
{
  int		i;
  int		e;
  char		*copy;

  i = 0;
  e = 0;
  copy = xmalloc((strlen_gnl(str) + size + 1) * sizeof(*copy));
  while (str != 0 && str[i] != '\0')
    {
      copy[i] = str[i];
      i++;
    }
  while (e < size)
    {
      copy[i] = buffer[e];
      i++;
      e++;
    }
  copy[i] = '\0';
  if (str != 0)
    free(str);
  return (copy);
}

char		*verif_gnl(char buffer[BUFF_SIZE], int *i)
{
  int		a;
  int		e;
  char		*str;

  a = 0;
  str = 0;
  while (a <= *i)
    {
      if (buffer[a++] == '\n')
        {
          e = 0;
          str = strconcate_gnl(str, buffer, a - 1);
          while (a <= *i)
            buffer[e++] = buffer[a++];
          *i = e - 1;
          return (str);
        }
    }
  return (0);
}

char		*get_next_line2(int nb,
				char buffer[BUFF_SIZE], int *i, char **str)
{
  int		e;

  e = 0;
  while (nb && buffer[(*i)++] != '\n')
    nb--;
  if (*i + 1 + READ_SIZE >= BUFF_SIZE && buffer[*i - 1] != '\n')
    {
      *str = strconcate_gnl(*str, buffer, *i);
      *i = 0;
    }
  else if (buffer[(*i) - 1] == '\n')
    *str = strconcate_gnl(*str, buffer, *i - 1);
  while (nb-- > 0)
    buffer[e++] = buffer[(*i)++];
  if (e != 0)
    {
      *i = e - 1;
      return (*str);
    }
  return (0);
}

char		*get_next_line(const int fd)
{
  static char	buffer[BUFF_SIZE];
  static int	i = 0;
  char		*str;
  int		nb;
  int		read_size;

  if (fd == -1)
    exit(EXIT_FAILURE);
  str = verif_gnl(buffer, &i);
  if (str != 0)
    return (str);
  read_size = (i + READ_SIZE >= BUFF_SIZE) ? BUFF_SIZE - (i + 1) : READ_SIZE;
  while ((nb = xread(fd, &buffer[i], read_size)))
    if ((get_next_line2(nb, buffer, &i, &str)))
      return (str);
  return (str);
}
