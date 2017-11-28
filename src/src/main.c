/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 13:32:37 by oabdalha          #+#    #+#             */
/*   Updated: 2017/10/22 17:48:44 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int main(int ac, char **av)
{
	t_flg flags;
	int		 i;
	t_dirs *dirs;

	flags = 0;
	(void)ac;
	i = flag_h(av + 1, &flags);
	dirs = dir_h(av + i, flags);
	ft_display(dirs, flags);
	memory_h(&dirs, DMM);
	exit(0);
}
