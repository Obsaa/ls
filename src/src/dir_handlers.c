/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:32:37 by oabdalha          #+#    #+#             */
/*   Updated: 2017/04/18 13:37:50 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_dirs *new_dir(char *path, int status, int is_default, char *subdir_name, t_flg flags)
{
	t_dirs *dir;
	DIR	*dr;
	struct stat f;

	MCH((dir = (t_dirs *)ft_memalloc(sizeof(t_dirs))));
	MCH((dir->name = ft_strdup(path)));
	MCH((dir->self = (t_files *)ft_memalloc(sizeof(t_files))));
	MCH((dir->self->name = ft_strdup(path)));
	if (status == ISLK)
	{
		if (!(dr = opendir(dir->name)) || flags & LLFG)
			status = ISND;
		else
			status = ISDR;
		if (dr)
			closedir(dr);
	}
	if (status != ISNE)
	{
		lstat(dir->name, &f);
		dir->date.msec = (unsigned long long)f.st_mtimespec.tv_sec;
		dir->date.mnsec = (unsigned long long)f.st_mtimespec.tv_nsec;
		dir->date.asec = (unsigned long long)f.st_atimespec.tv_sec;
		dir->date.ansec = (unsigned long long)f.st_atimespec.tv_nsec;
		dir->date.csec = (unsigned long long)f.st_ctimespec.tv_sec;
		dir->date.cnsec = (unsigned long long)f.st_ctimespec.tv_nsec;
		dir->date.bsec = (unsigned long long)f.st_birthtimespec.tv_sec;
		dir->date.bnsec = (unsigned long long)f.st_birthtimespec.tv_nsec;
		MCH((dir->self->display_name = ft_strdup(path)));
		dir->self->ISDR_info = 1;
		if (subdir_name)
			MCH((dir->display_name = ft_strdup(subdir_name)));
	}
	dir->status = status;
	dir->next = NULL;
	dir->is_default = is_default;
	dir->is_unreadable = 0;
	dir->total_blocks = 0;
	dir->file_count = 0;
	dir->has_valid_files = 0;
	dir->max_file_len = 0;
	return (dir);
}

void add_dir(t_dirs **dirs, t_dirs *new) {
	t_dirs *tmp;
	t_dirs *head;

	tmp = *dirs;
	head = tmp;
	while (tmp->next)
			tmp = tmp->next;
	tmp->next = new;
	*dirs = head;
}

void reverse_dirs(t_dirs **dirs)
{
	t_dirs *curr;
	t_dirs *next;
	t_dirs *prev;

	prev = NULL;
	curr = *dirs;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*dirs = prev;
}

void set_dir(char *path, t_dirs **dirs, char *subdir_name, t_flg flags) {
	t_dirs *new;
	int status;
	struct stat f;

	status = ISDR;
	if (lstat(path, &f) == -1)
	{
		if (ENOENT == errno)
			status = ISNE;
	}
	else
	{
		if (!S_ISDIR(f.st_mode))
			status = ISND;
	}
	if (S_ISLNK(f.st_mode))
		status = ISLK;
	new = new_dir(path, status, 0, subdir_name, flags);
	if (!*dirs || (*dirs)->is_default)
		*dirs = new;
	else
		add_dir(dirs, new);
}

t_dirs *dir_handler(char **args, t_flg flags) {
	int i;
	t_dirs *dirs;
	t_etarget target;
	t_dirs *tmp;

	dirs = new_dir(".", ISDR, 1, 0, flags);
	i = -1;
	while (args[++i])
	{
			if (args[i][0] == '\0')
			{
				MCH((target.file = ft_strdup("fts_open")));
				error_handler(NER, target);
				free(target.file);
				exit(1);
			}
			set_dir(args[i], &dirs, NULL, flags);
	}

	if (flags & FISS)
	{
		tmp = dirs;
		while (tmp)
		{
			add_file(&tmp->self, &tmp, flags, IDLF);
			tmp = tmp->next;
		}
	}
	dir_sort(&dirs, flags);
	return (dirs);
}
