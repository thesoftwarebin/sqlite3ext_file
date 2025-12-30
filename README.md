This is a SQLite extension that provides a few file management SQL functions:

```
	SELECT FILE_DATE_MODIFIED(PATHNAME);                        -- returns a date like '2025-12-29 00:42:00', or NULL if error
	SELECT FILE_SIZE(PATHNAME);                                 -- returns file size as an integer, or NULL if error
	SELECT FILE_EXISTS(PATHNAME);                               -- returns 'true' or 'false' or 'error'
	
	SELECT FILE_EXTENSION(PATHNAME);                            -- returns file extension including the dot (".jpg"), or empty string if not found
	SELECT FILE_FILENAME(PATHNAME);                             -- returns filename without folders, but including extension; "/" is the folder separator
	SELECT FILE_BASENAME(PATHNAME);                             -- returns filename without folders and without extension; "/" is the folder separator
	SELECT FILE_UPDIR(PATHNAME);                                -- returns the folder containing this file; "/" is the folder separator
	
	SELECT BLOB_CRC32(BLOBCONTENT);                             -- returns the CRC32 hex string (8 hex digits) for this blob, or "FFFFFFFF" if error or empty file
	SELECT FILE_CRC32(PATHNAME);                                -- returns the CRC32 hex string (8 hex digits) for this file, or "FFFFFFFF" if error or empty file
	
	SELECT FILE_MKDIR(DIRNAME);                                 -- returns either "OK" or a string starting with "error"
	SELECT FILE_TO_FILE(SOURCEPATHNAME, DESTINATIONPATHNAME);   -- returns either "OK" or a string starting with "error"
```

All these functions except `BLOB_CRC32` are capable of handling files ≥1GB. Although no extensive tests have been conducted about the maximum file size, there functions have been tested on a 5+GB file:

- `FILE_EXISTS`
- `FILE_SIXE`
- `FILE_CRC32`
- `FILE_TO_FILE`

See [test/test002-basic.sql](test/test002-basic.sql) and [test/test003-write.sql](test/test003-write.sql) for a few more usage examples.

### How to compile

```
	configure
	make all
	ls -l src/.libs/sqlite3ext_file*.dll # binary is generated here
```

### How to run the test suite

```
	configure # or "configure --with-bigfiletests" if you want to test also files >= 4GB
	make all  # compile binaries before running the test
	make check
```

The tests have been confirmed to pass on MinGW64 in Windows, with this setup:

```
	# OS is: Microsoft Windows 11 Home 10.0.26200 build 26200

	$ uname -a
	MINGW64_NT-10.0-26200 PC-ROSS 3.6.4-23a25d49.x86_64 2025-07-16 16:15 UTC x86_64 Msys
	
	$ which gcc
	/mingw64/bin/gcc
	
	$ gcc --version
	gcc.exe (Rev8, Built by MSYS2 project) 15.1.0

	$ autoconf --version
	autoconf (GNU Autoconf) 2.72

	$ make --version
	GNU Make 4.4.1
	Built for x86_64-pc-msys
```

At the time of writing (Dec'2025) no tests have been conducted on
Linux or other Unix-like OSes, but the source code is supposed to
compile and run there with no or minimal adjustments.
