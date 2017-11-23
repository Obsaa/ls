/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 05:38:48 by oabdalha          #+#    #+#             */
/*   Updated: 2016/11/26 05:39:55 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"


char	*ft_strnchr(char *s, char c, int offset)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (s + i + offset);
	return (NULL);
}
