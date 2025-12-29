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

#include "libsqlitefile_pathname.h"
#include "libsqlitefile_common.h"

#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

extern const sqlite3_api_routines *sqlite3_api;

void libsqlitefile_pathname_get_extension(sqlite3_context * context, int argc, sqlite3_value ** argv){
	char result[PATHNAME_MAX_LENGTH+1];
	const char *path = sqlite3_value_text(argv[0]);
	const char* p1=strrchr(path, PATH_EXTENSION_SEPARATOR);
	const char* p2=strrchr(path, PATHNAME_SEPARATOR);

	if (p1==NULL || (p2!=NULL && p1<p2)){
		sqlite3_result_text(context, "", -1, SQLITE_STATIC);
	} else {
		sqlite3_result_text(context, p1, -1, SQLITE_TRANSIENT);
	}
	return;
}

const char* get_filename(const char* path);

const char* get_filename(const char* path){
	const char* p1 = strrchr(path, PATHNAME_SEPARATOR);
	if (p1==NULL){
		return path;
	} else {
		return p1+1;
	}
}

void libsqlitefile_pathname_get_filename(sqlite3_context * context, int argc, sqlite3_value ** argv){
	const char *path = sqlite3_value_text(argv[0]);
	const char* p1 = get_filename(path);
	sqlite3_result_text(context, p1, -1, SQLITE_TRANSIENT);
	return;
}

void get_basename(const char* path, char* dest_basename, const size_t dest_basename_size);

void get_basename(const char* path, char* dest_basename, const size_t dest_basename_size){
	const char* p1=get_filename(path);
	const char* p2=strrchr(p1, PATH_EXTENSION_SEPARATOR);
	if (p2==NULL){
		strncpy(dest_basename, p1, dest_basename_size-1);
	} else {
		strncpy(dest_basename, p1, ((p2>p1)? p2-p1 : dest_basename_size-1));
		dest_basename[p2-p1]='\0';
	}
}
void libsqlitefile_pathname_get_basename(sqlite3_context * context, int argc, sqlite3_value ** argv){
	const char *path = (char *) sqlite3_value_text(argv[0]);
	char result[PATHNAME_MAX_LENGTH+1];
	get_basename(path, result, sizeof(result)/sizeof(char));
	sqlite3_result_text(context, result, -1, SQLITE_TRANSIENT);
	return;
}

void libsqlitefile_pathname_get_updir(sqlite3_context * context, int argc, sqlite3_value ** argv){
	char result[PATHNAME_MAX_LENGTH+1];
	const char *path = (char *) sqlite3_value_text(argv[0]);
	if (!up_dir(path, result)){
		sqlite3_result_null(context);
	} else {
		sqlite3_result_text(context, result, -1, SQLITE_TRANSIENT);
	}
	return;
}
