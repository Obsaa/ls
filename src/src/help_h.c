/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 13:32:37 by oabdalha          #+#    #+#             */
/*   Updated: 2017/10/22 17:48:44 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		usage_help(void)
{
	print_h(1, "Usage: ./ft_ls [OPTION]... [FILE]...\n", 0, NULL);
	print_h(1, "List information about the FILEs (the current directory b\
y default).\n", 0, NULL);
	print_h(1, "Sort entries alphabetically if -t is n\
ot specified.\n", 0, NULL);
}

void		arguments_help(void)
{
	print_h(1, "Mandatory arguments to long options are mandatory f\
or short options too.\n", 0, NULL);
	print_h(1, "	-l\t\t\tuse a long listing format\n", 0, NULL);
	print_h(1, "	-R, --recursive\tlist subdirectories re\
cursively\n", 0, NULL);
	print_h(1, "	-a, --all\t\tdo not ignore entries st\
arting with .\n", 0, NULL);
	print_h(1, "	-r, --reverse\t\treverse order while sorting\n", 0, NULL);
	print_h(1, "	-t\t\t\tsort by modifica\
tion time, newest first\n", 0, NULL);
}

void		exits_help(void)
{
	print_h(1, "Exit status:\n", 0, NULL);
	print_h(1, " 0	if OK,\n", 0, NULL);
	print_h(1, " 1	if minor problems (e.g., cannot acce\
ss subdirectory),\n", 0, NULL);
	print_h(1, " 2	if serious trouble (e.g., cann\
ot access command-line argument).\n", 0, NULL);
}

void		help_h(void)
{
	usage_help();
	print_h(1, "\n", 0, NULL);
	arguments_help();
	print_h(1, "\n", 0, NULL);
	exits_help();
 	exit(0);
}
