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
#include "libsqlitefile_last_modification_date.h"
#include "libsqlitefile_common.h"

#include <string.h>
#include <sqlite3.h>
#include <time.h>
#include <sys/stat.h>

#ifdef HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
	#include "fopen_utf8.h"
#endif

/* functions used only in this module */
void sqlite_date_string_from_file(const char* path, char* destination_buffer, const int destination_buffer_length);
void unix_timestamp_to_sqlite_date_string(const time_t unixTimestamp, char* destination_buffer, const int destination_buffer_length);

void unix_timestamp_to_sqlite_date_string(const time_t unixTimestamp, char* destination_buffer, const int destination_buffer_length){
	struct tm * ptm = localtime(&unixTimestamp);
	if (ptm!=NULL){
		if (strftime (destination_buffer, destination_buffer_length, "%Y-%m-%d %H:%M:%S", ptm) != 0){
			return;
		} else {
			strcpy(destination_buffer, "");
			return;
		}
	} else {
		strcpy(destination_buffer, "");
		return;
	}
}

void sqlite_date_string_from_file(const char* path, char* destination_buffer, const int destination_buffer_length){

	struct stat b;

	#ifdef HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
		wchar_t wpath[PATHNAME_MAX_LENGTH+1];
		utf8_to_utf16(path, wpath);
		const int stat_result = wstat(wpath, &b);
	#else
		const int stat_result = stat(path, &b);
	#endif

	if (!stat_result) {
		unix_timestamp_to_sqlite_date_string(b.st_mtime, destination_buffer, destination_buffer_length);
		return;
	} else {
		strcpy(destination_buffer, "");
		return;
	}
}

extern const sqlite3_api_routines *sqlite3_api;

/* library function */
void libsqlitefile_last_modification_date(sqlite3_context * context, int argc, sqlite3_value ** argv){
	char *path = (char *) sqlite3_value_text(argv[0]);
	int destination_buffer_length=100;
	char destination_buffer[100+1];
	sqlite_date_string_from_file(path, destination_buffer, destination_buffer_length);
	sqlite3_result_text(context, destination_buffer, -1, SQLITE_TRANSIENT);
	return;
}

