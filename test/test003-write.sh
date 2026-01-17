# -*- coding: utf-8 -*-

if [ ! -f "${srcdir}/test/test003-write.sql" ] ; then exit 99 ; fi

if [ -f "./src/.libs/sqlite3ext_file-1.dll" ] ; then
	libtotest="./src/.libs/sqlite3ext_file-1.dll"
elif [ -f "./src/.libs/sqlite3ext_file.so.1" ] ; then
	libtotest="./src/.libs/sqlite3ext_file.so.1"
else
	echo "error: cannot find the binary library to test (so or .dll file)"
	exit 99
fi

idir="${srcdir}/test/inputdata"
odir="./test/test003-output"

olog="${odir}/test003-write.sql.log"

rm -vrf "${odir}"

mkdir -p "${odir}"
mkdir -p "${odir}/file_to_file_existing_dir"

sqlite3 :memory: ".load \"${libtotest}\"" ".param init" ".param set @idir \"${idir}\"" ".param set @odir \"${odir}\"" ".read \"${srcdir}/test/test003-write.sql\"" > "${olog}"

cat "${olog}"

if grep -q FAILED "${odir}/test003-write.sql.log" ; then
	# exit with failure if at least one test has FAILED
	exit 1
else
	# no tests are FAILED, they were either PASSED or SKIPPED
	exit 0
fi
