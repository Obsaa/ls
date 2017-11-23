/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha<jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 22:23:42 by oabdalha          #+#    #+#             */
/*   Updated: 2017/04/15 18:36:20 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"


void	ft_putstr_fd(char const *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
