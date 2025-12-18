/*
    Copyright 2025 by Andrea Rossetti <andrear1979@hotmail.com>

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config.h"
#include "libsqlitefile_size.h"
#include "libsqlitefile_common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include <sqlite3ext.h>

#ifdef HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
	#include "fopen_utf8.h"
#endif

void file_size(char* path, char* result, int result_size);

void file_size(char* path, char* result, int result_size){

#ifdef HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
	wchar_t wpath[PATHNAME_MAX_LENGTH+1];
	utf8_to_utf16(path, wpath);
	struct stat64 b;
	const auto stat_result = wstat64(wpath, &b);
#else
	struct stat b;
	const auto stat_result = stat(path, &b);
#endif

	if (!stat_result) {
		sprintf(result, "%llu", b.st_size);
	} else {
		strcpy(result, "");
	}
	return;
}

extern const sqlite3_api_routines *sqlite3_api;

void libsqlitefile_size(sqlite3_context * context, int argc, sqlite3_value ** argv){
	char result[100+1];
	char *path = (char *) sqlite3_value_text(argv[0]);

	if (file_exists(path)>0){
		file_size(path, result, 100);
		sqlite3_result_text(context, result, -1, SQLITE_TRANSIENT);
	} else {
		sqlite3_result_null(context);
	}
	return;
}

