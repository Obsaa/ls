#include "../inc/ft_ls.h"

void initialize_format(t_frmt *format)
{
  format->dtmn = 3;
  format->dtdy = 2;
  format->dthr = 2;
  format->dmin = 2;
  format->dtyr = 5;
  format->link = 0;
  format->owner = 0;
  format->group = 0;
  format->flsz = 0;
  format->usrd = 0;
  format->grpi = 0;
  format->major = 0;
  format->minor = 0;
}

void format_handler(t_frmt *format, t_files *file, int format_option) {
  if (format_option == IDLF)
    return ;
  if (format_option == INIF)
    initialize_format(format);
  if (format->link < ft_intlen(file->link))
    format->link = ft_intlen(file->link);
  if (format->owner < (int)ft_strlen(file->owner))
    format->owner = (int)ft_strlen(file->owner);
  if (format->group < (int)ft_strlen(file->group))
    format->group = (int)ft_strlen(file->group);
  if (format->flsz < ft_intlen(file->size))
    format->flsz = ft_intlen(file->size);
  if (format->usrd < ft_intlen(file->usrd))
    format->usrd = ft_intlen(file->usrd);
  if (format->grpi < ft_intlen(file->grpi))
    format->grpi = ft_intlen(file->grpi);
  if (format->major < ft_intlen(file->major))
    format->major = ft_intlen(file->major);
  if (format->minor < ft_intlen(file->minor))
    format->minor = ft_intlen(file->minor);
}
