/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <oabdalha@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 13:32:37 by oabdalha          #+#    #+#             */
/*   Updated: 2017/10/18 13:37:50 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H
#include "../libft/includes/libft.h"
#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/time.h>
#include <glob.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define MCH(x) if (!x) exit(2)

#define DMM 1
#define EMM 2

#define FER 1
#define FAR 2
#define NER 4

#define ISNE 1
#define ISND 2
#define ISDR 4
#define ISLK 8
#define ISUR 16

#define ISUSR 1
#define ISGRP 2
#define ISOTH 4

#define CRED  "\x1b[31m"
#define CGRE  "\x1b[32m"
#define CBGR  "\x1b[32;1m"
#define CYEL  "\x1b[33m"
#define CBLU  "\x1b[34m"
#define CMAG  "\x1b[35m"
#define CBCY  "\x1b[96;1m"
#define CRES  "\x1b[0m"

#define ISNP(c) (c <= ' ' && c >= '~')

#define INIF 1
#define UFOR 2
#define IDLF 4

typedef struct s_frmt {
  int link;
  int owner;
  int group;
  int flsz;
  int dtmn;
  int dtdy;
  int dthr;
  int dmin;
  int dtyr;
  int usrd;
  int grpi;
  int major;
  int minor;
} t_frmt;

typedef enum s_flg {
  LLFG = 1, // -l
  REFG = 2, // -R
  ALLG = 4, // -a
  REVF = 8, // -r
  MDST = 16, // -t
  DUAG = 32, // -n
  SUPO = 64, // -g
  OEPL = 128, // -1
  CODI = 256, // -C
  CRDS = 512, // -U
  LADS = 1024, // -a
  LSCS = 2048, // -c
  HCPD = 4096, // -A
  FISS = 8192, // -S
  COOP = 16384 // -G
} t_flg;

typedef struct s_dt {
  char *month;
  char *day;
  char *hour;
  char *minute;
  char *year;
  unsigned long long msec;
  unsigned long long mnsec;
  unsigned long long asec;
  unsigned long long ansec;
  unsigned long long csec;
  unsigned long long cnsec;
  unsigned long long bsec;
  unsigned long long bnsec;
} t_dt;

typedef struct s_files {
  char *modes;
  long link;
  char *owner;
  unsigned int usrd;
  char *group;
  unsigned int grpi;
  long size;
  t_dt date;
  char *name;
  int isdin;
  long major;
  long minor;
  int iscbk;
  int is_link;
  char *lnkdt;
  int hnpc;
  char *disna;
  int status;
  struct s_files *next;
  struct stat f; // Since I'm passing this I don't need to do stuffs like is_link or iscbk
} t_files;

typedef struct s_dirs {
  char *name;
  int status;
  t_files *files;
  t_files *self;
  t_frmt format;
  int       isdef;
  int       isunr;
  int       tobl;
  struct s_dirs *sdirs;
  struct s_dirs *next;
  int file_count;
  int max_file_len;
  t_dt date;
  int issub;
  char *disna;
  int hcob;
  int hvfi;
} t_dirs;

typedef union u_etarget {
  char flag;
  char *file;
} t_etarget;


typedef union u_entries {
  t_files *files;
  char **file_names;
} t_entries;

void help_handler(void);
t_dirs *dir_handler(char **args, t_flg flags);
int flag_handler(char **args, t_flg *flags);
void error_handler(int err, t_etarget target);
void display_handler(t_dirs *head, t_dirs *dirs, t_flg flags, int target);
t_files *file_handler(t_dirs *dirs, t_flg flags);
void set_dir(char *path, t_dirs **dirs, char *subdir_name, t_flg flags);
void add_file(t_files **curr_file, t_dirs **dirs, t_flg flags, int format_option);
void add_dir(t_dirs **dirs, t_dirs *new);
void format_handler(t_frmt *format, t_files *file, int format_option);
int is_last_dir(t_dirs *dirs);
t_dirs *subdir_handler(t_dirs *next, t_dirs **sdirs, t_flg flags);
void memory_handler(void *mem_target, int target);
int is_last_nondir(t_dirs *dirs);
int is_only_dir(t_dirs *head);
void file_sort(t_files **files, t_flg flags);
int has_dirs(t_dirs *dirs);
void dir_sort(t_dirs **dirs, t_flg flags);
void reverse_files(t_files **files);
void reverse_dirs(t_dirs **dirs);
void ft_display(t_dirs *dirs, t_flg flags);
char get_file_entry_type(int mode);
char third_permission_mode_handler(int mode, int userType);
char **argument_handler(int ac, char **av);
t_frmt get_nondir_format(t_dirs **dirs, t_flg flags);
void print_handler(int fd, char *str, int format, char *target);
void lprint_handler(int fd, char *str, int format, char *target);
#endif
