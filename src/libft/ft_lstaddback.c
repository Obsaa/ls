/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 00:01:01 by oabdalha          #+#    #+#             */
/*   Updated: 2017/03/29 00:01:03 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"


void	ft_lstaddback(t_list **alst, t_list *new)
{
    t_list  *tmp;
    t_list  *head;

    tmp = *alst;
    head = tmp;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
	*alst = head;
}
