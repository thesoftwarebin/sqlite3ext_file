/*
	This is a slightly modified version of fopen_utf8.h, which came with public domain license.
	The initial version had been downloaded from here: https://github.com/Photosounder/fopen_utf8/blob/596768da5be62031f0325761baacf2ddb2c8d72e/fopen_utf8.h

	The modifications to that original file come under these license terms:

	Copyright 2025 by Andrea Rossetti <andrear1979@hotmail.com>

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#include "config.h"

#ifdef HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES

#ifndef H_FOPEN_UTF8
#define H_FOPEN_UTF8
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

extern int utf8_char_size(const uint8_t *c);
extern uint32_t utf8_to_unicode32(const uint8_t *c, size_t *index);
extern int codepoint_utf16_size(uint32_t c);
extern uint16_t *sprint_utf16(uint16_t *str, uint32_t c);
extern size_t strlen_utf8_to_utf16(const uint8_t *str);
extern uint16_t *utf8_to_utf16(const uint8_t *utf8, uint16_t *utf16);

extern FILE *fopen_utf8(const char *path, const char *mode);

#ifdef __cplusplus
}
#endif
#endif

#endif // HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
