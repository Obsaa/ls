/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha<jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 01:39:09 by oabdalha          #+#    #+#             */
/*   Updated: 2017/01/17 22:39:47 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"


char	*ft_strstr(const char *big, const char *little)
{
	int		i;
	int		j;
	int		k;
	int		good;

	if (!ft_strlen(little))
		return ((char *)big);
	i = -1;
	good = 0;
	while (*(big + ++i) && !good)
	{
		if (*(big + i) == *(little + 0))
		{
			j = 0;
			k = i;
			good = 1;
			while (*(little + j))
				if (*(little + j++) != *(big + k++))
					good = 0;
			if (good)
				return ((char *)big + i);
		}
	}
	return (NULL);
}