#include "../inc/ft_ls.h"

t_dirs *subdir_handler(t_dirs *next, t_dirs **sdirs, t_flg flags)
{
  t_dirs *tmp;

  if (!*sdirs)
    return (next);
  dir_sort(sdirs, flags);
  if (flags & REVF)
    reverse_dirs(sdirs);
  tmp = *sdirs;
  while (tmp->next) {
    tmp = tmp->next;
  }
  tmp->next = next;
  return (*sdirs);
}
