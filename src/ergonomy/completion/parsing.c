/*
** parsing.c for 42sh in /home/snap/projects/42sh/current
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Thu May  6 11:22:03 2010 botton vivien
** Last update Sun May 23 13:42:33 2010 philippe berenguel
*/

#include <stdlib.h>
#include "lib_includes/strings.h"

static char	*get_command_exp(char *str, int *mode)
{
  int		p;
  char		*new_str;

  p = my_strlen(str);
  while (p > 0 && str[p] != ';' && str[p] != '|' && str[p] != '<' &&
	 str[p] != '>' && str[p] != '(' && str[p] != ')' && str[p] != '&')
    p--;
  if (str[p] == '<' || str[p] == '>' || str[p] == ')')
    *mode = 1;
  else if (str[p] == '&' && p > 0 && (str[p - 1] == '<' || str[p - 1] == '>'))
    *mode = 1;
  if (p > 0)
    p++;
  else if (str[p] == '(' || str[p] == ';' || str[p] == '|' || str[p] == '&')
    p++;
  while (str[p] != '\0' && (str[p] == ' ' || str[p] == '\t'))
    p++;
  new_str = my_strdup(&str[p]);
  if (new_str[0] == '\0')
    {
      free(new_str);
      return (NULL);
    }
  return (new_str);
}

static char	*parsing_part2(char *str, int i, int p)
{
  char		*new_str;

  if (str[i - 1] == ' ' || str[i - 1] == '\t')
    return (NULL);
  if (str[p] != '\0' && (str[p + 1] == ' ' || str[p + 1] == '\t'))
    {
      p++;
      while (str[p] == ' ' || str[p] == '\t')
	p++;
    }
  new_str = my_strndup((str + p), (i - p));
  free(str);
  if (my_strcmp(new_str, "..") == 0)
    new_str = my_strcat(FIRST_FREE, new_str, "/", NULL);
  return (new_str);
}

char		*parsing(char *str, int *mode)
{
  int		i;
  char		*new_str;
  char		*cur_str;
  int		p;

  cur_str = get_command_exp(str, mode);
  if (cur_str == NULL)
    return (NULL);
  p = my_strlen(cur_str);
  i = p;
  while (p > 0 && cur_str[p] != ' ' && cur_str[p] != '\t' && cur_str[p] != '&'
	 && cur_str[p] != '|' && cur_str[p] != ';')
    p--;
  if (p == i)
    *mode = 1;
  else if (p > 0 && (cur_str[p] == ' ' || cur_str[p] == '\t'))
    {
      while (p > 0 && (cur_str[p] == ' ' || cur_str[p] == '\t'))
	p--;
      if (p > 0)
	*mode = 2;
    }
  new_str = parsing_part2(cur_str, i, p);
  return (new_str);
}
