/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendswith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha<jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 20:56:49 by oabdalha          #+#    #+#             */
/*   Updated: 2017/01/17 23:58:22 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"


int   ft_strendswith(char *s1, char *s2)
{
    int     i;

    i = -1;
    while (s1[++i])
        if (s1[i] == s2[0])
            if (ft_strcmp(s1 + i, s2) == 0)
                return (1);
    return (0);
}
