/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 13:32:37 by oabdalha          #+#    #+#             */
/*   Updated: 2017/10/22 17:48:44 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int is_last_dir(t_dirs *dirs)
{
	t_dirs *tmp;

	tmp = dirs->next;
	while (tmp)
	{
		if (tmp->status == ISDR)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int last_nand(t_dirs *dirs)
{
	t_dirs *tmp;

	tmp = dirs->next;
	while (tmp)
	{
		if (tmp->status == ISND)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int has_dirs(t_dirs *dirs)
{
	t_dirs *tmp;

	tmp = dirs;
	while (tmp)
	{
		if (tmp->status == ISDR)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_frmt nand_f(t_dirs **dirs, t_flg flags)
{
	t_frmt format;
	t_dirs *tmp;
	int format_option;

	tmp = *dirs;
	format_option = INIF;
	while (tmp)
	{
		if (tmp->status == ISND)
		{
			add_file(&tmp->self, &tmp, flags, INIF);
			if (flags & LLFG)
				format_h(&format, tmp->self, format_option);
			format_option = UFOR;
		}
		tmp = tmp->next;
	}
	return (format);
}