#ifndef SCM_IOEXT_H
#define SCM_IOEXT_H

/* Copyright 1995-1998,2000-2001,2006,2008,2018
     Free Software Foundation, Inc.

   This file is part of Guile.

   Guile is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Guile is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
   License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with Guile.  If not, see
   <https://www.gnu.org/licenses/>.  */



#include "libguile/scm.h"



SCM_API SCM scm_ftell (SCM object);
SCM_API SCM scm_redirect_port (SCM into_pt, SCM from_pt);
SCM_API SCM scm_dup_to_fdes (SCM fd_or_port, SCM newfd);
SCM_API SCM scm_dup2 (SCM oldfd, SCM newfd);
SCM_API SCM scm_fileno (SCM port);
SCM_API SCM scm_isatty_p (SCM port);
SCM_API SCM scm_fdopen (SCM fdes, SCM modes);
SCM_API SCM scm_primitive_move_to_fdes (SCM port, SCM fd);
SCM_API SCM scm_fdes_to_ports (SCM fd);
SCM_INTERNAL void scm_init_ioext (void);

#endif  /* SCM_IOEXT_H */
