/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 13:32:37 by oabdalha          #+#    #+#             */
/*   Updated: 2017/10/22 17:48:44 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void print_h(int fd, char *str, int format, char *target)
{
		char *new;
		char *tmp;

		if (!format && !target)
				return (ft_putstr_fd(str, fd));
		MCH((new = ft_strnew(format + ft_strlen(str) + ft_strlen(target) - 2)));
		int len = (int)ft_strlen(target);
		int i = -1;
		while (str[++i])
		{
				if (str[i] == '%')
				{
						while (len++ < format) {
								tmp = new;
								new = ft_strjoinch(new, ' ');
								free(tmp);
						}
						tmp = new;
						MCH((new = ft_strjoin(new, target)));
						free(tmp);
						i += (str[i + 1] == 'd' || str[i + 1] == 's') ? 1 : 2;
				}
				else {
						tmp = new;
						MCH((new = ft_strjoinch(new, str[i])));
						free(tmp);
				}
		}
		ft_putstr_fd(new, fd);
		free(new);
}

void lprint_h(int fd, char *str, int format, char *target)
{
		char *new;
		char *tmp;

		if (!format && !target)
				return (ft_putstr_fd(str, fd));
		MCH((new = ft_strnew(format + ft_strlen(str) + ft_strlen(target) - 2)));
		int len = (int)ft_strlen(target);
		int i = -1;
		while (str[++i])
		{
				if (str[i] == '%')
				{
						tmp = new;
						MCH((new = ft_strjoin(new, target)));
						free(tmp);
						while (len++ < format) {
								tmp = new;
								new = ft_strjoinch(new, ' ');
								free(tmp);
						}
						i += (str[i + 1] == 'd' || str[i + 1] == 's') ? 1 : 2;
				}
				else {
						tmp = new;
						MCH((new = ft_strjoinch(new, str[i])));
						free(tmp);
				}
		}
		ft_putstr_fd(new, fd);
		free(new);
}