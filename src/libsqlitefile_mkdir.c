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

#include "libsqlitefile_mkdir.h"
#include "libsqlitefile_common.h"

#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <sqlite3ext.h>

extern const sqlite3_api_routines *sqlite3_api;

/* TODO: return more error messages */
void libsqlitefile_mkdir(sqlite3_context * context, int argc,
		sqlite3_value ** argv) {
	char *dirpath = (char *) sqlite3_value_text(argv[0]);
	switch(libsqlitefile_mkdir_with_file(dirpath, 0)){
		case 0:
			sqlite3_result_text(context, "error on libsqlitefile_mkdir", -1, SQLITE_STATIC);
			break;
		case 1:
			sqlite3_result_text(context, "OK", -1, SQLITE_STATIC);
			break;
	}
}
