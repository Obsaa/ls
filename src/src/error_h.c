/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 13:32:37 by oabdalha          #+#    #+#             */
/*   Updated: 2017/10/22 17:48:44 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void				error_h(int err, t_etar target)
{
		if (err == FER)
		{
				print_h(2, "ls: illegal option -- -\n", 0, NULL);
				print_h(2, "usage: ls [-ABCFGHLOPRS\
TUWabcdefghiklmnopqrstuwx1] [file ...]\n", 0, NULL);
				print_h(2, "Try './ft_ls --help' for more information.\n", 0, NULL);
				exit(1);
		}
		else if (err == NER)
				print_h(2, "./ft_ls: %s: No such file or directory\n", 0, target.file);
		else
				print_h(2, "./ft_ls: %s: Permission denied\n", 0, target.file);
}
