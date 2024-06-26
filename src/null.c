/*
 * cwdaemon - morse sounding daemon for the parallel or serial port
 * Copyright (C) 2002 - 2005 Joop Stakenborg <pg4i@amsat.org>
 *                      and many authors, see the AUTHORS file.
 * Copyright (C) 2012 - 2024 Kamil Ignacak <acerion@wp.pl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "config.h"

#if HAVE_STRING_H
# if !STDC_HEADERS && HAVE_MEMORY_H
#  include <memory.h>
# endif
# include <string.h>
#endif

#include "cwdaemon.h"

/**
   \file null.c - null port functions

   The functions do, well, nothing, except for provide convenient
   placeholder.
*/

int null_probe_cwdevice(const char *fname)
{
	if (strcmp(fname, "null") != 0) {
		return -1;
	} else {
		return 0;
	}
}

int null_init(cwdevice *dev, int fd)
{
	dev->fd = fd;
	return 0;
}

int null_free(__attribute__((unused)) cwdevice *dev)
{
	return 0;
}

int null_reset_pins_state(__attribute__((unused)) cwdevice * dev)
{
	return 0;
}

int null_cw(__attribute__((unused)) cwdevice *dev, __attribute__((unused)) int onoff)
{
	return 0;
}

int null_ptt(__attribute__((unused)) cwdevice *dev, __attribute__((unused)) int onoff)
{
	return 0;
}
