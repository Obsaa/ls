/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha<jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:33:27 by oabdalha          #+#    #+#             */
/*   Updated: 2017/01/15 10:18:18 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int     ft_strstartswith(char *s1, char *s2)
{
    int     i;

    i = -1;
    while (s2[++i])
        if (s1[i] != s2[i])
            return (0);
    return (1);
}