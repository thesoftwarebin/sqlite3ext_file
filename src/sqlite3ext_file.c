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

#include <stdlib.h>

#include "libsqlitefile_file_to_file.h"
#include "libsqlitefile_crc32.h"
#include "libsqlitefile_mkdir.h"
#include "libsqlitefile_last_modification_date.h"
#include "libsqlitefile_size.h"
#include "libsqlitefile_exists.h"
#include "libsqlitefile_pathname.h"

#include <sqlite3ext.h>

SQLITE_EXTENSION_INIT1;

#define SQLITE_EXTENSION_ADD_FUNCTION(db,fn_name,args,fn_code)        \
	sqlite3_create_function(                                          \
		(db),                                                         \
		(fn_name),                                                    \
		(args),                                                       \
		SQLITE_UTF8,                                                  \
		NULL,                                                         \
		(fn_code),                                                    \
		NULL,                                                         \
		NULL                                                          \
	)

/* SQLite invokes this routine once when it loads the extension. */
int sqlite3_extension_init(sqlite3 * db, char **pzErrMsg, const sqlite3_api_routines * pApi){
	int retval=0;
	SQLITE_EXTENSION_INIT2(pApi);
	retval|=SQLITE_EXTENSION_ADD_FUNCTION(db, "file_mkdir",         1, libsqlitefile_mkdir);
	retval|=SQLITE_EXTENSION_ADD_FUNCTION(db, "file_to_file",       2, libsqlitefile_file_to_file);
	retval|=SQLITE_EXTENSION_ADD_FUNCTION(db, "blob_crc32",         1, libsqlitefile_blob_crc32);
	retval|=SQLITE_EXTENSION_ADD_FUNCTION(db, "file_crc32",         1, libsqlitefile_file_crc32);
	retval|=SQLITE_EXTENSION_ADD_FUNCTION(db, "file_date_modified", 1, libsqlitefile_last_modification_date);
	retval|=SQLITE_EXTENSION_ADD_FUNCTION(db, "file_size",          1, libsqlitefile_size);
	retval|=SQLITE_EXTENSION_ADD_FUNCTION(db, "file_exists",        1, libsqlitefile_exists);
	retval|=SQLITE_EXTENSION_ADD_FUNCTION(db, "file_extension",     1, libsqlitefile_pathname_get_extension);
	retval|=SQLITE_EXTENSION_ADD_FUNCTION(db, "file_filename",      1, libsqlitefile_pathname_get_filename);
	retval|=SQLITE_EXTENSION_ADD_FUNCTION(db, "file_basename",      1, libsqlitefile_pathname_get_basename);
	retval|=SQLITE_EXTENSION_ADD_FUNCTION(db, "file_updir",         1, libsqlitefile_pathname_get_updir);
	return retval;
}
