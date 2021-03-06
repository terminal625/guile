/* Copyright 2008,2018
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

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <pthread.h>
#include <libguile.h>

void *thread_inner_main (void *unused);
void *thread_main (void *unused);
void *do_join (void *data);
void *inner_main (void *unused);

void *
thread_inner_main (void *unused)
{
  int argc = 3;
  char *argv[] = {
    "guile",
    "-c",
    "(or (current-module) (exit -1))",
    0
  };

  scm_shell (argc, argv);

  return NULL;			/* dummy */
}

void *
thread_main (void *unused)
{
  scm_with_guile (&thread_inner_main, NULL);

  return NULL;			/* dummy */
}

void *
do_join (void *data)
{
  pthread_t *thread = (pthread_t *) data;

  pthread_join (*thread, NULL);

  return NULL;			/* dummy */
}

void *
inner_main (void *unused)
{
  pthread_t thread;

  pthread_create (&thread, NULL, &thread_main, NULL);
  scm_without_guile (do_join, &thread);

  return NULL;			/* dummy */
}

int
main (int argc, char **argv)
{
  scm_with_guile (&inner_main, NULL);

  return 0;
}
