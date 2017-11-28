/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_h2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 13:32:37 by oabdalha          #+#    #+#             */
/*   Updated: 2017/10/22 17:48:44 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void move_file(t_files **destRef, t_files **sourceRef)
{
	t_files *new;

	new = *sourceRef;
	*sourceRef = (*sourceRef)->next;
	new->next = *destRef;
	*destRef = new;
}

void hfmc(t_files **a, t_files **b, t_files **tmp, t_flg flags)
{
	int comparison;

	// Try to do '<'' instead of '<=' to see if it would improve speed
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
		comparison = (*a)->size >= (*b)->size;
		if ((*a)->size == (*b)->size)
			comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
	}
	move_file(tmp, comparison ? a : b);
}

t_files *merge_splitted_files(t_files *a, t_files *b, t_flg flags)
{
	t_files *res;
	t_files **tmp;

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
		hfmc(&a, &b, tmp, flags);
		tmp = &((*tmp)->next);
	}
	return (res);
}

void split_file(t_files *sourceRef, t_files **frontRef, t_files **backRef)
{
	t_files *slow;
	t_files *fast;

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

void file_sort(t_files **files, t_flg flags)
{
	t_files *head;
	t_files *a;
	t_files *b;

	head = *files;
	if (!head || !head->next)
		return ;
	split_file(head, &a, &b);
	file_sort(&a, flags);
	file_sort(&b, flags);
	*files = merge_splitted_files(a, b, flags);
}
