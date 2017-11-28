/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_h3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:40:08 by oabdalha          #+#    #+#             */
/*   Updated: 2017/04/18 04:29:44 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

char file_entry(int mode)
{
  if (S_ISBLK(mode))
    return ('b');
  else if (S_ISCHR(mode))
    return ('c');
  else if (S_ISDIR(mode))
    return ('d');
  else if (S_ISLNK(mode))
    return ('l');
  else if (S_ISSOCK(mode))
    return ('s');
  else if (S_ISFIFO(mode))
    return ('p');
  else
    return ('-');
}

void reverse_files(t_files **files)
{
  t_files *curr;
  t_files *next;
  t_files *prev;

  prev = NULL;
  curr = *files;
  while (curr)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  *files = prev;
}

char get_correct_character(int mode, int isExec, int isSticky)
{
    if (mode & isExec)
    {
        if (mode & isSticky)
            return ('s');
        else
            return ('x');
    }
    else
    {
        if (mode & isSticky)
            return ('S');
        else
            return ('-');
    }
}

char perm_mod_h(int mode, int userType)
{
    if (userType == ISUSR)
        return get_correct_character(mode, S_IXUSR, S_ISUID);
    else if (userType == ISGRP)
        return get_correct_character(mode, S_IXGRP, S_ISGID);
    else
    {
        if (mode & S_IXOTH)
        {
            if (mode & S_ISTXT)
                return ('t');
            else
                return ('x');
        }
        else
        {
            if (mode & S_ISTXT)
                return ('T');
            else
                return ('-');
        }
    }
}