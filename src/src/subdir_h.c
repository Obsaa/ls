/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subdir_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 13:32:37 by oabdalha          #+#    #+#             */
/*   Updated: 2017/10/22 17:48:44 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_dirs *subdir_h(t_dirs *next, t_dirs **sdirs, t_flg flags)
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
