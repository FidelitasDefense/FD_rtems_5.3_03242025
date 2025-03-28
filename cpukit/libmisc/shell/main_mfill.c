/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 * 
 * @brief MFILL Shell Command Implementation
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

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <rtems.h>
#include <rtems/shell.h>
#include <rtems/stringto.h>
#include "internal.h"

static int rtems_shell_main_mfill(
  int   argc,
  char *argv[]
)
{
  unsigned long  tmp;
  void          *addr;
  size_t         size;
  unsigned char  value;

  if ( argc != 4 ) {
    fprintf(stderr,"%s: too few arguments\n", argv[0]);
    return -1;
  }

  /*
   *  Convert arguments into numbers
   */
  if ( rtems_string_to_pointer(argv[1], &addr, NULL) ) {
    printf( "Address argument (%s) is not a number\n", argv[1] );
    return -1;
  }

  if ( rtems_string_to_unsigned_long(argv[2], &tmp, NULL, 0) ) {
    printf( "Size argument (%s) is not a number\n", argv[2] );
    return -1;
  }
  size = (size_t) tmp;

  if ( rtems_string_to_unsigned_char(argv[3], &value, NULL, 0) ) {
    printf( "Value argument (%s) is not a number\n", argv[3] );
    return -1;
  }

  /*
   *  Now fill the memory.
   */
  memset(addr, value, size);

  return 0;
}

rtems_shell_cmd_t rtems_shell_MFILL_Command = {
  "mfill",                                      /* name */
  "mfill address size value",                   /* usage */
  "mem",                                        /* topic */
  rtems_shell_main_mfill,                       /* command */
  NULL,                                         /* alias */
  NULL                                          /* next */
};
