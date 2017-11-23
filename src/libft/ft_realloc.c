/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 01:11:53 by oabdalha          #+#    #+#             */
/*   Updated: 2016/10/21 01:11:56 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"


void		*ft_realloc(void *ptr, size_t size)
{
	void		*new_ptr;

	if (!ptr || !size)
		return (NULL);
	if (!(new_ptr = ft_strnew(size)))
		return (NULL);
	ft_strcpy(new_ptr, ptr);
	return (new_ptr);
}
