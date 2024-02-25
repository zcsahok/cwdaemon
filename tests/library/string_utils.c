/*
 * This file is a part of cwdaemon project.
 *
 * Copyright (C) 2003, 2006 Joop Stakenborg <pg4i@amsat.org>
 * Copyright (C) 2012 - 2024 Kamil Ignacak <acerion@wp.pl>
 *
 * Some of this code is taken from netkeyer.c, which is part of the tlf source,
 * here is the copyright:
 * Tlf - contest logging program for amateur radio operators
 * Copyright (C) 2001-2002-2003 Rein Couperus <pa0rct@amsat.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */




/**
   @file

   String utils
*/




#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "string_utils.h"




/*
  Function uses '{' and '}' characters to enclose escaped characters because
  these two characters aren't in a set of Morse code characters. This means
  that they can't be easily mistaken with valid characters processed during
  regular tests.
*/
char * escape_string(const char * buffer, char * escaped, size_t size)
{
	/* TODO: acerion: add better control of indexes: check if printing to
	   output buffer doesn't go beyond buffer boundary. */
	size_t e_idx = 0;

	for (size_t i = 0; i < strlen(buffer); i++) {
		const char character = buffer[i];
		if (isprint((unsigned char) character)) {
			if (e_idx < size - 1) {
				escaped[e_idx++] = character;
			} else {
				goto L_NO_SPACE;
			}
		} else {
			switch (character) {
			case '\r':
				if (e_idx < size - 4) {
					escaped[e_idx++] = '{';
					escaped[e_idx++] = 'C';
					escaped[e_idx++] = 'R';
					escaped[e_idx++] = '}';
				} else {
					goto L_NO_SPACE;
				}
				break;
			case '\n':
				if (e_idx < size - 4) {
					escaped[e_idx++] = '{';
					escaped[e_idx++] = 'L';
					escaped[e_idx++] = 'F';
					escaped[e_idx++] = '}';
				} else {
					goto L_NO_SPACE;
				}
				break;
			default:
				if (e_idx < size - 6) {
					e_idx += snprintf(escaped + e_idx, size - e_idx, "{0x%02x}", (unsigned char) character);
				} else {
					goto L_NO_SPACE;
				}
				break;
			}
		}
	}

	escaped[e_idx] = '\0';
	return escaped;

 L_NO_SPACE:
	for (; e_idx < size - 1; e_idx++) {
		escaped[e_idx] = '#';
	}
	escaped[size - 1] = '\0';
	return escaped;
}


