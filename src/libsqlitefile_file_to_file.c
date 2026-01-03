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
*/

#include "config.h"
#include "libsqlitefile_common.h"
#include "libsqlitefile_file_to_file.h"

#include <stdlib.h>
#include <string.h>
#include <sqlite3ext.h>
#include <unistd.h>
#include <fcntl.h>
#include <utime.h>

#ifdef HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
	#include "fopen_utf8.h"
#endif

extern const sqlite3_api_routines *sqlite3_api;

void libsqlitefile_file_to_file(sqlite3_context * context, int argc,
		sqlite3_value ** argv) {
	char file_name_src[PATHNAME_MAX_LENGTH+1];
	char file_name_dst[PATHNAME_MAX_LENGTH+1];
	strcpy(file_name_src, (char *) sqlite3_value_text(argv[0]));
	strcpy(file_name_dst, (char *) sqlite3_value_text(argv[1]));

#ifdef HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
	wchar_t wfile_name_src[PATHNAME_MAX_LENGTH+1];
	wchar_t wfile_name_dst[PATHNAME_MAX_LENGTH+1];
	wcscpy(wfile_name_src, (wchar_t*) sqlite3_value_text16(argv[0]));
	wcscpy(wfile_name_dst, (wchar_t*) sqlite3_value_text16(argv[1]));
	const int src_equals_dst = (_wcsicmp(wfile_name_src, wfile_name_dst)==0);
#else
	const int src_equals_dst = (stricmp(file_name_src, file_name_dst)==0);
#endif

	int fd_src;
	int fd_dst;

	if (src_equals_dst){
		sqlite3_result_text(context, "error because source and destination have same name", -1, SQLITE_STATIC);
		return;
	} else if (!libsqlitefile_mkdir_with_file(file_name_dst /*char* path*/, 1 /*int is_path_of_a_file*/)){
		sqlite3_result_text(context, "error on mkdir", -1, SQLITE_STATIC);
		return;
	} else if (
		(fd_src=
			#ifdef HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
						_wopen(wfile_name_src, O_BINARY | O_RDONLY)
			#else
						open(file_name_src, O_BINARY | O_RDONLY)
			#endif
		)==-1
	){
		sqlite3_result_text(context, "error opening source file", -1, SQLITE_STATIC);
		return;
	} else if (
		(fd_dst=
#ifdef HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
				_wopen(wfile_name_dst, O_BINARY | O_WRONLY | O_TRUNC | O_CREAT)
#else
				open(file_name_dst, O_BINARY | O_WRONLY | O_TRUNC | O_CREAT)
#endif
		)==-1
	){
		close(fd_src);
		sqlite3_result_text(context, "error opening destination file", -1, SQLITE_STATIC);
		return;
	} else {
		unsigned char buffer[FILE_TO_FILE_BUFFER_SIZE];

		ssize_t n;
		while((n=read(fd_src, buffer, FILE_TO_FILE_BUFFER_SIZE)) > 0){
			write_buffer_incrementally(buffer, n, fd_dst);
		}
		close(fd_dst);

		/* alter last access/modification time */
		struct utimbuf timbuf_src;
		if (file_to_file_mtime_sec(fd_src, &(timbuf_src.modtime))==1){
			timbuf_src.actime=timbuf_src.modtime;
			utime(file_name_dst, &(timbuf_src));
		}

		close(fd_src);
	}

	sqlite3_result_text(context, "OK", -1, SQLITE_STATIC);
	return;
}
