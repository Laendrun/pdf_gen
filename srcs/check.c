#include "laendrun.h"

int ft_char_is_num(char c)
{
  if (c >= 48 && c <= 57)
    return (1);
  return (0);
}

int ft_str_is_num(char *str)
{
  int i = 0;
  while (str[i])
  {
    if (ft_char_is_num(str[i]))
      i++;
    else
      return (0);
  }
  return (1);
}

int ft_check_client_format(char *str)
{
  int i = 3;
  if (str[0] == 'C' && str[1] == 'L' && str[2] == 'T')
  {
    while (i < 8)
    {
      if (ft_char_is_num(str[i]))
        i++;
      else
        return (0);
    }
    return (1);
  }
  return (0);
}