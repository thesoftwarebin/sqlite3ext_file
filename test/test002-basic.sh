# -*- coding: utf-8 -*-

if [ ! -f "${srcdir}/test/test002-basic.sql" ] ; then exit 99 ; fi

idir="${srcdir}/test/inputdata"
odir="./test/test002-output"

rm -rf "${odir}"
mkdir -p "${odir}"

olog="${odir}/test002-basic.sql.log"

# forcing an exact date-time on this peculiar file because modification date is later validated by a SQL test
touch -t 202511262355.38 "${idir}/test-città.png"

sqlite3.exe :memory: ".load \"./src/.libs/sqlite3ext_file-1.dll\"" ".param init" ".param set @idir \"${idir}\"" ".read \"${srcdir}/test/test002-basic.sql\"" > "${olog}"

if grep -q FAILED "${olog}" ; then
	# fail if at least one test has FAILED 
	exit 1
else
	# no tests are FAILED, they were either PASSED or SKIPPED 
	exit 0
fi
