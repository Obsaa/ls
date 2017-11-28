/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 13:32:37 by oabdalha          #+#    #+#             */
/*   Updated: 2017/10/22 17:48:44 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include <stdio.h>

void file_date_handler(t_dt *date, struct stat f, t_flg flags) {
	char buff[200];
	unsigned long long t;

	date->msec = (unsigned long long)f.st_mtimespec.tv_sec;
	date->mnsec = (unsigned long long)f.st_mtimespec.tv_nsec;
	date->asec = (unsigned long long)f.st_atimespec.tv_sec;
	date->ansec = (unsigned long long)f.st_atimespec.tv_nsec;
	date->csec = (unsigned long long)f.st_ctimespec.tv_sec;
	date->cnsec = (unsigned long long)f.st_ctimespec.tv_nsec;
	date->bsec = (unsigned long long)f.st_birthtimespec.tv_sec;
	date->bnsec = (unsigned long long)f.st_birthtimespec.tv_nsec;
	t = date->msec;
	if (flags & CRDS)
		t = date->bsec;
	if (flags & LADS)
		t = date->asec;
	if (flags & LSCS)
	t = date->csec;
	strftime(buff, 200, "%b", localtime((const long *)&t));
	MCH((date->month = ft_strdup(buff)));
	strftime(buff, 200, "%-d", localtime((const long *)&t));
	MCH((date->day = ft_strdup(buff)));
	strftime(buff, 200, "%H", localtime((const long *)&t));
	MCH((date->hour = ft_strdup(buff)));
	strftime(buff, 200, "%M", localtime((const long *)&t));
	MCH((date->minute = ft_strdup(buff)));
	strftime(buff, 200, "%Y", localtime((const long *)&t));
	MCH((date->year = ft_strdup(buff)));
}

char extended_attributes_handler(char *file_path)
{
	char res;
	acl_t acl;
	acl_entry_t entry;

	res = ' ';
	if (listxattr(file_path, NULL, 0, XATTR_NOFOLLOW) == -1)
	{
		if (errno == EPERM || errno == EACCES || errno == EFAULT)
			return (' ');
	}
	else if (listxattr(file_path, NULL, 0, XATTR_NOFOLLOW) > 0)
		return ('@');
	acl = acl_get_link_np(file_path, ACL_TYPE_EXTENDED);
	if (!acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if (acl)
		res = '+';
	return (res);
}

char *serialize_file_name(char *name, int len)
{
	char *new;
	int i;
	char c;

	MCH((new = ft_strnew(ft_strlen(name))));
	i = -1;
	while (i < len && name[i]) {
		c = name[i];
		if (ISNP(name[i]))
		{
			if (name[i] == '\r')
				c = '?';
			else
				c = ' ';
		}
		new[i] = c;
	}
	return (new);
}

int hnpc(char *s, int len)
{
	int i;

	i = -1;
	while (++i < len && s[i])
		if (ISNP(s[i]))
			return (1);
	return (0);
}

void file_permission_handler(t_files **curr_file, char *file_path, struct stat f)
{
	(*curr_file)->modes[0] = file_entry(f.st_mode);
	(*curr_file)->modes[1] = (f.st_mode & S_IRUSR) ? 'r' : '-';
	(*curr_file)->modes[2] = (f.st_mode & S_IWUSR) ? 'w' : '-';
	(*curr_file)->modes[3] = perm_mod_h(f.st_mode, ISUSR);
	(*curr_file)->modes[4] = (f.st_mode & S_IRGRP) ? 'r' : '-';
	(*curr_file)->modes[5] = (f.st_mode & S_IWGRP) ? 'w' : '-';
	(*curr_file)->modes[6] = perm_mod_h(f.st_mode, ISGRP);
	(*curr_file)->modes[7] = (f.st_mode & S_IROTH) ? 'r' : '-';
	(*curr_file)->modes[8] = (f.st_mode & S_IWOTH) ? 'w' : '-';
	(*curr_file)->modes[9] = perm_mod_h(f.st_mode, ISOTH);
	if ((*curr_file)->modes[1] != '-')
		(*curr_file)->modes[10] = extended_attributes_handler(file_path);
	else
		(*curr_file)->modes[10] = ' ';
}

void get_file_info(t_files **curr_file, t_dirs **dirs, char *file_path, int format_option, t_flg flags)
{
	char buff[256];
	struct stat f;

	f = (*curr_file)->f;
	file_permission_handler(curr_file, file_path, f);
	(*curr_file)->link = f.st_nlink;
	(*curr_file)->owner = getpwuid(f.st_uid) ? ft_strdup(getpwuid(f.st_uid)->pw_name) : NULL;
	(*curr_file)->group = getgrgid(f.st_gid) ? ft_strdup(getgrgid(f.st_gid)->gr_name) : NULL;
	(*curr_file)->usrd = (int)f.st_uid;
	(*curr_file)->grpi = (int)f.st_gid;
	(*curr_file)->size = f.st_size;
	if (S_ISCHR(f.st_mode) || S_ISBLK(f.st_mode))
	{
		(*curr_file)->major = (long)major(f.st_rdev);
		(*curr_file)->minor = (long)minor(f.st_rdev);
		(*curr_file)->iscbk = 1;
		if (!(*dirs)->hcob)
			(*dirs)->hcob = 1;
	}
	if (S_ISLNK(f.st_mode))
	{
		(*curr_file)->is_link = 1;
		int link_len = 0;
		if ((link_len = readlink(file_path, buff, 256)) == -1)
			exit(2);
		if (hnpc(buff, link_len)) {
			MCH(((*curr_file)->lnkdt = serialize_file_name(buff, link_len)));
		}
		else {
			MCH(((*curr_file)->lnkdt = ft_strndup(buff, link_len)));
		}
	}
	file_date_handler(&((*curr_file)->date), f, flags);
	format_h(&(*dirs)->format, *curr_file, format_option);
}

void add_file(t_files **curr_file, t_dirs **dirs, t_flg flags, int format_option)
{
	char *dir_name;
	char *file_path;
	int file_name_len;

	dir_name = (*dirs)->name;
	file_path = (*curr_file)->isdin ? (*curr_file)->name : ft_pathjoin(dir_name, (*curr_file)->name);
	if (lstat(file_path, &(*curr_file)->f) < 0)
	{
		if (errno == ENOENT)
			(*curr_file)->status = ISNE;
		else if (errno == EACCES)
			(*curr_file)->status = ISUR;
		return ;
	}
	(*dirs)->hvfi = 1;
	MCH(((*curr_file)->modes = ft_strnew(11)));
	get_file_info(curr_file, dirs, file_path, format_option, flags);
	if ((flags & LLFG) && !(*curr_file)->isdin)
	{
		if ((*dirs)->status == ISDR)
			(*dirs)->tobl += (*curr_file)->f.st_blocks;
	}
	else
	{
		(*dirs)->file_count++;
		file_name_len = ft_strlen((*curr_file)->name);
		if (file_name_len > (*dirs)->max_file_len)
			(*dirs)->max_file_len = file_name_len;
	}
	if (S_ISDIR((*curr_file)->f.st_mode) && (flags & REFG) && !ft_strequ((*curr_file)->name, "..") && !ft_strequ((*curr_file)->name, ".")) {
		set_dir(ft_pathjoin(dir_name, (*curr_file)->name), &((*dirs)->sdirs), (*curr_file)->name, flags);
	}
}

// Make this a libft function
char *get_entry_name(char *path)
{
	char **parts;

	MCH((parts = ft_strsplit(path, '/')));
	int i = -1;
	while (parts[++i])
	{
		if (!parts[i + 1])
			return (parts[i]);
	}
	return (path);
}

t_files *file_h(t_dirs *dirs, t_flg flags) {
	DIR	 *dir;
	struct dirent *sd;
	t_files *files;
	t_files **tmp;
	int format_option;
	char *file_name;

	if (!(dir = opendir(dirs->name)))
	{
		dirs->isunr = 1;
		MCH((dirs->disna = get_entry_name(dirs->name)));
		return (NULL);
	}
	files = NULL;
	tmp = &files;
	format_option = INIF;
	while ((sd = readdir(dir)))
	{
		if (flags & HCPD && !(flags & ALLG) && (ft_strequ(sd->d_name, ".") || ft_strequ(sd->d_name, "..")))
			continue ;
		if (!(flags & ALLG) && !(flags & HCPD) && sd->d_name[0] == '.')
			continue ;
		MCH(((*tmp = (t_files *)ft_memalloc(sizeof(t_files)))));
		file_name = sd->d_name;
		if (hnpc(sd->d_name, ft_strlen(sd->d_name))) {
			(*tmp)->disna = serialize_file_name(sd->d_name, ft_strlen(sd->d_name));
			(*tmp)->hnpc = 1;
		}
		(*tmp)->name = ft_strdup(sd->d_name);
		add_file(tmp, &dirs, flags, format_option);
		format_option = UFOR;
		tmp = &((*tmp)->next);
	}
	closedir(dir);
	file_sort(&files, flags);
	return (files);
}
