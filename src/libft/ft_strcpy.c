/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:25:07 by oabdalha          #+#    #+#             */
/*   Updated: 2017/03/24 02:49:18 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"


char	*ft_strcpy(char *dst, const char *src)
{
	int		i;

	i = -1;
	while (*(src + ++i))
		*(dst + i) = *(src + i);
	*(dst + i) = '\0';
	return (dst);
}
