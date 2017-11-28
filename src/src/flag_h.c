/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:40:08 by oabdalha          #+#    #+#             */
/*   Updated: 2017/04/18 04:29:44 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void long_option_flag(char *option, t_flg *flags) {
  t_etar target;

  if (ft_strequ(option, "help"))
    help_h();
  else if (ft_strequ(option, "recursive"))
    *flags |= REFG;
  else if (ft_strequ(option, "all"))
    *flags |= ALLG;
  else if (ft_strequ(option, "reverse"))
    *flags |= REVF;
  else {
    target.flag = '-';
    error_h(FER, target);
  }
}

void display_flag_h(t_flg *flags, char f)
{
  if (f == '1')
  {
    if (*flags & CODI)
      *flags &= ~CODI;
    if (*flags & LLFG)
      *flags &= ~LLFG;
    *flags |= OEPL;
  }
  else if (f == 'l' || f == 'g')
  {
    if (f == 'g')
      *flags |= SUPO;
    if (*flags & CODI)
      *flags &= ~CODI;
    if (*flags & OEPL)
      *flags &= ~OEPL;
    *flags |= LLFG;
  }
  else
  {
    if (*flags & OEPL)
      *flags &= ~OEPL;
    if (*flags & LLFG)
      *flags &= ~LLFG;
    *flags |= CODI;
  }
}

void sort_flag_h(t_flg *flags, char f)
{
  if (f == 't' && !(*flags & FISS))
    *flags |= MDST;
  else if (f == 'U')
  {
    if (*flags & LADS)
      *flags &= ~LADS;
    if (*flags & LSCS)
      *flags &= ~LSCS;
    *flags |= CRDS;
  }
  else if (f == 'u')
  {
    if (*flags & CRDS)
      *flags &= ~CRDS;
    if (*flags & LSCS)
      *flags &= ~LSCS;
    *flags |= LADS;
  }
  else if (f == 'c')
  {
    if (*flags & CRDS)
      *flags &= ~CRDS;
    if (*flags & LADS)
      *flags &= ~LADS;
    *flags |= LSCS;
  }
  else
  {
    if (*flags & MDST)
      *flags &= ~MDST;
    *flags |= FISS;
  }
}

void set_flag(char *arg, t_flg *flags) {
  int i;
  t_etar target;

  if (ft_strstartswith(arg, "--") && arg[2])
    return long_option_flag(arg + 2, flags);
  i = 0;
  while (arg[++i]) {
    if (arg[i] == 'R')
      *flags |= REFG;
    else if (arg[i] == 'a')
      *flags |= ALLG;
    else if (arg[i] == 'r')
      *flags |= REVF;
    else if (arg[i] == 'n')
      *flags |= DUAG;
    else if (arg[i] == 'A')
      *flags |= HCPD;
    else if (arg[i] == 'G')
      *flags |= COOP;
    else if (arg[i] == 'U' || arg[i] == 't' || arg[i] == 'u' || arg[i] == 'c' || arg[i] == 'S')
      sort_flag_h(flags, arg[i]);
    else if (arg[i] == '1' || arg[i] == 'l' || arg[i] == 'C' || arg[i] == 'g')
      display_flag_h(flags, arg[i]);
    else {
      target.flag = arg[i];
      error_h(FER, target);
    }
  }
}

int flag_h(char **args, t_flg *flags) {
  int i;

  i = -1;
  *flags |= CODI;  
  while (args[++i]) {
    if (args[i][0] != '-')
      break;
    if (ft_strequ(args[i], "--")) {
      i++;
      break;
    }
    if (args[i][0] == '-' && args[i][1])
      set_flag(args[i], flags);
    else
      break;
  }
  return (i > 0 ? i + 1 : 1);
}
