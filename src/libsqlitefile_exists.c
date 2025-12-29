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

#include "libsqlitefile_exists.h"
#include "libsqlitefile_common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include <sqlite3.h>

extern const sqlite3_api_routines *sqlite3_api;

void libsqlitefile_exists(sqlite3_context * context, int argc, sqlite3_value ** argv){
	const char *path = (char *) sqlite3_value_text(argv[0]);
	const int r=file_exists(path);
	sqlite3_result_text(context, ((r>0)? "true" : ((r==0)? "false" : "error")), -1, SQLITE_TRANSIENT);
	return;
}

