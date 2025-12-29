/*
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

	Created on: 2012-10-18
*/

#ifndef LIBSQLITEFILE_COMMON_H_
#define LIBSQLITEFILE_COMMON_H_

#include <sys/time.h>

/* start of
configuration and default values; they can
be overridden in gcc using -DSYMBOL=VALUE
*/
#ifndef PATHNAME_SEPARATOR
#define PATHNAME_SEPARATOR '/'
#endif

#ifndef PATH_EXTENSION_SEPARATOR
#define PATH_EXTENSION_SEPARATOR '.'
#endif

#ifndef PATHNAME_MAX_LENGTH
#define PATHNAME_MAX_LENGTH 65536
#endif
/* end of
configuration and default values; they can
be overridden in gcc using -DSYMBOL=VALUE
*/

int file_stats(const char* filename);
int file_exists(const char* filename);
int libsqlitefile_mkdir_with_file(const char* path, const int is_path_of_a_file);
int write_buffer_incrementally(const unsigned char *blob_buffer, int blob_buffer_size, int fd);
int file_to_file_mtime_sec(int fd, time_t *timespec_dest);
int up_dir(const char* path, char* dir_buffer);

#ifdef DEBUG
#include <stdio.h>
#define log_errors(a,b,c) printf((a),(b),(c))
#else
#define log_errors(a,b,c)
#endif

#endif /* LIBSQLITEFILE_COMMON_H_ */
