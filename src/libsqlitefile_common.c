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

#include "config.h"
#include "libsqlitefile_common.h"

#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <io.h>
#include <direct.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
	#include "fopen_utf8.h"
#endif

int up_dir(const char* path, char* dir_buffer){
	char* p1=strrchr(path, PATHNAME_SEPARATOR);
	if (p1!=NULL){
		strncpy(dir_buffer, path, p1-path);
		dir_buffer[p1-path]='\0';
		return 1;
	} else {
		return 0;
	}
}

int file_stats(const char* filename){
	struct stat64 s;
	memset(&s, 0, sizeof(struct stat64));

#ifdef HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
	wchar_t wfilename[PATHNAME_MAX_LENGTH+1];
	utf8_to_utf16(filename, wfilename);
	int result=wstat64(wfilename, &s);
#else
	int result=stat64(filename, &s);
#endif
	
	if (result==-1){
		if (errno==ENOENT){
			return 0;
		} else {
			return -1;
		}
	} else {
		if (S_ISDIR(s.st_mode)){
			return 1;
		} else if (S_ISREG(s.st_mode)){
			return 2;
		} else {
			return 3;
		}
	}
}

int file_exists(const char* filename){
	int ret=file_stats(filename);
	return (ret==0 || ret==-1)? ret : 1;
}

int libsqlitefile_mkdir_with_file(const char* path, const int is_path_of_a_file){
	char dirpath[PATHNAME_MAX_LENGTH+1];
	log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d)...\n", path, is_path_of_a_file);
	if (is_path_of_a_file){
		switch(file_stats(path)){
			case 0:
				if (up_dir(path, dirpath)){
					int result=libsqlitefile_mkdir_with_file(dirpath, 0);
					if (result==0){
						log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 0 (libsqlitefile_mkdir_with_file(dirpath, 0) failed)\n", path, is_path_of_a_file);
						return 0;
					}
				}
				log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 1 (not found but upper dir is ok)\n", path, is_path_of_a_file);
				return 1;
			case 1:
				log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 0 (not a file, it's a dir)\n", path, is_path_of_a_file);
				return 0;
			case 2:
				log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 1 (found and upper dir is ok)\n", path, is_path_of_a_file);
				return 1;
			case 3:
				log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 0 (not a regular file and not a directory)\n", path, is_path_of_a_file);
				return 0;
			default:
				log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 0 (file_stats returned unexpected value)\n", path, is_path_of_a_file);
				return 0;
		}
	} else {
		switch(file_stats(path)){
			case 1:
				log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 1 (dir already exists)\n", path, is_path_of_a_file);
				return 1;
			case 2:
				log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 0 (not a dir, it's a file)\n", path, is_path_of_a_file);
				return 0;
			case 0:
				if (up_dir(path, dirpath)){
					if (libsqlitefile_mkdir_with_file(dirpath, 0)==0){
						log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 0 (error on mkdir_wrapper of parent)\n", path, is_path_of_a_file);
						return 0;
					};
				}

				#ifdef HAVE_SUPPORT_FOR_WIN32_UTF8_PATHNAMES
					wchar_t wpath[PATHNAME_MAX_LENGTH+1];
					utf8_to_utf16(path, wpath);
					const int mkdir_result = _wmkdir(wpath);
				#else
					const int mkdir_result = mkdir(path);
				#endif

				if (mkdir_result==0){
					log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 1 (mkdir has been called)\n", path, is_path_of_a_file);
					return 1;
				} else {
					log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 0 (error on mkdir)\n", path, is_path_of_a_file);
					return 0;
				}
			case 3:
				log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 0 (not a regular file and not a directory)\n", path, is_path_of_a_file);
				return 0;
			case -1:
				log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 0 (unexpected stats from file)\n", path, is_path_of_a_file);
				return 0;
			default:
				log_errors("libsqlitefile_mkdir_with_file(\"%s\", %d) returns 0 (unexpected return value from file_exists(...))\n", path, is_path_of_a_file);
				return 0;
		}
	}
}

int write_buffer_incrementally(const unsigned char *blob_buffer, int blob_buffer_size, int fd){
	int n=write(fd, blob_buffer, blob_buffer_size);
	while (n>=0 && n<blob_buffer_size){
			blob_buffer+=n;
			blob_buffer_size-=n;
			n=write(fd, blob_buffer, blob_buffer_size);
	}
	return (blob_buffer_size==n)? 0: -1;
}

int file_to_file_mtime_sec(int fd, time_t *timespec_dest){
	struct stat s;
	memset(&s, 0, sizeof(struct stat));
	int result=fstat(fd, &s);
	if (result==-1){
		if (errno==ENOENT){
			return 0;
		} else {
			return -1;
		}
	} else {
		memcpy(timespec_dest, &(s.st_mtime), sizeof(time_t));
		return 1;
	}
}
