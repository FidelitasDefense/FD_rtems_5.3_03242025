/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 * 
 * @brief chmod Shell Command Implementation
 */

/*
 * Copyright (C) 2001 Fernando Ruiz Casas <fruizcasas@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <rtems.h>
#include <rtems/shell.h>
#include <rtems/stringto.h>
#include "internal.h"

static int rtems_shell_main_chmod(
  int argc,
  char *argv[]
)
{
  int           n;
  mode_t        mode;
  unsigned long tmp;
  int           sc;

  if (argc < 2) {
    fprintf(stderr,"%s: too few arguments\n", argv[0]);
    return -1;
  }

  /*
   *  Convert arguments into numbers
   */
  if ( rtems_string_to_unsigned_long(argv[1], &tmp, NULL, 0) ) {
    printf( "Mode argument (%s) is not a number\n", argv[1] );
    return -1;
  }
  mode = (mode_t) (tmp & 0777);

  /*
   *  Now change the files modes
   */
  for (n=2 ; n < argc ; n++) {
    sc = chmod(argv[n], mode);
    _Assert_Unused_variable_unequal(sc, -1);
  }

  return 0;
}

rtems_shell_cmd_t rtems_shell_CHMOD_Command = {
  "chmod",                                      /* name */
  "chmod 0777 n1 n2... # change filemode",      /* usage */
  "files",                                      /* topic */
  rtems_shell_main_chmod,                       /* command */
  NULL,                                         /* alias */
  NULL                                          /* next */
};
