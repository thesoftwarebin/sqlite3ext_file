# -*- coding: utf-8 -*-

if [ ! -f "${srcdir}/test/test002-basic.sql" ] ; then exit 99 ; fi

if [ -f "./src/.libs/sqlite3ext_file-1.dll" ] ; then
	libtotest="./src/.libs/sqlite3ext_file-1.dll"
elif [ -f "./src/.libs/sqlite3ext_file.so.1" ] ; then
	libtotest="./src/.libs/sqlite3ext_file.so.1"
else
	echo "error: cannot find the binary library to test (so or .dll file)"
	exit 99
fi

idir="${srcdir}/test/inputdata"
odir="./test/test002-output"

rm -rf "${odir}"
mkdir -p "${odir}"

olog="${odir}/test002-basic.sql.log"

# forcing an exact date-time on this peculiar file because modification date is later validated by a SQL test
touch -t 202511262355.38 "${idir}/test-modified-date.png"

sqlite3 :memory: ".load \"${libtotest}\"" ".param init" ".param set @idir \"${idir}\"" ".read \"${srcdir}/test/test002-basic.sql\"" > "${olog}"

if grep -q FAILED "${olog}" ; then
	# fail if at least one test has FAILED 
	exit 1
else
	# no tests are FAILED, they were either PASSED or SKIPPED 
	exit 0
fi
