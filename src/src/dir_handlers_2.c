/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_handlers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:32:37 by oabdalha          #+#    #+#             */
/*   Updated: 2017/04/18 13:37:50 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void move_dir(t_dirs **destRef, t_dirs **sourceRef)
{
  t_dirs *new;

  new = *sourceRef;
  *sourceRef = (*sourceRef)->next;
  new->next = *destRef;
  *destRef = new;
}

void handle_dir_merge_comparison(t_dirs **a, t_dirs **b, t_dirs **tmp, t_flg flags)
{
  int comparison;

  comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
  if (flags & MDST)
  {
    comparison = (*a)->date.msec >= (*b)->date.msec;
    if ((*a)->date.msec == (*b)->date.msec)
    {
      comparison = (*a)->date.mnsec >= (*b)->date.mnsec;
      if ((*a)->date.mnsec == (*b)->date.mnsec)
        comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
    }
    if (flags & CRDS)
    {
      comparison = (*a)->date.bsec >= (*b)->date.bsec;
      if ((*a)->date.bsec == (*b)->date.bsec)
      {
        comparison = (*a)->date.bnsec >= (*b)->date.bnsec;
        if ((*a)->date.bnsec == (*b)->date.bnsec)
          comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
      }
    }
    else if (flags & LADS)
    {
      comparison = (*a)->date.asec >= (*b)->date.asec;
      if ((*a)->date.asec == (*b)->date.asec)
      {
        comparison = (*a)->date.ansec >= (*b)->date.ansec;
        if ((*a)->date.ansec == (*b)->date.ansec)
          comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
      }
    }
    else if (flags & LSCS)
    {
      comparison = (*a)->date.csec >= (*b)->date.csec;
      if ((*a)->date.csec == (*b)->date.csec)
      {
        comparison = (*a)->date.cnsec >= (*b)->date.cnsec;
        if ((*a)->date.cnsec == (*b)->date.cnsec)
          comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
      }
    }
  }
  else if (flags & FISS)
  {
    comparison = (*a)->self->size >= (*b)->self->size;
    if ((*a)->self->size == (*b)->self->size)
      comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
  }
  move_dir(tmp, comparison ? a : b);
}

t_dirs *merge_splitted_dirs(t_dirs *a, t_dirs *b, t_flg flags)
{
  t_dirs *res;
  t_dirs **tmp;

  res = NULL;
  tmp = &res;
  while (1)
  {
    if (!a)
    {
      *tmp = b;
      break;
    }
    else if (!b)
    {
      *tmp = a;
      break;
    }
    handle_dir_merge_comparison(&a, &b, tmp, flags); 
    tmp = &((*tmp)->next);
  }
  return (res);
}

void split_dirs(t_dirs *sourceRef, t_dirs **frontRef, t_dirs **backRef)
{
  t_dirs *slow;
  t_dirs *fast;

  slow = sourceRef;
  fast = sourceRef->next;
  while (fast)
  {
    fast = fast->next;
    if (fast)
    {
      slow = slow->next;
      fast = fast->next;
    }
  }
  *frontRef = sourceRef;
  *backRef = slow->next;
  slow->next = NULL;
}

void dir_sort(t_dirs **dirs, t_flg flags)
{
  t_dirs *head;
  t_dirs *a;
  t_dirs *b;

  head = *dirs;
  if (!head || !head->next)
    return ;
  split_dirs(head, &a, &b);
  dir_sort(&a, flags);
  dir_sort(&b, flags);
  *dirs = merge_splitted_dirs(a, b, flags);
}
