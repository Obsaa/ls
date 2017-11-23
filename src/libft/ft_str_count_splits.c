/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_count_splits.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 05:11:45 by oabdalha          #+#    #+#             */
/*   Updated: 2017/03/21 01:08:38 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"


int		ft_str_count_splits(const char *str, char seps)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		str = ft_find_next(str, seps, 1);
		if (*str != '\0')
		{
			i++;
			str = ft_find_next(str, seps, 0);
		}
	}
	return (i);
}
