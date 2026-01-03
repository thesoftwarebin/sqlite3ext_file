# -*- coding: utf-8 -*-

if [ ! -f "${srcdir}/test/test003-write.sql" ] ; then exit 99 ; fi

idir="${srcdir}/test/inputdata"
odir="./test/test003-output"

olog="${odir}/test003-write.sql.log"

rm -vrf "${odir}"

mkdir -p "${odir}"
mkdir -p "${odir}/file_to_file_existing_dir"

sqlite3.exe :memory: ".load \"./src/.libs/sqlite3ext_file-1.dll\"" ".param init" ".param set @idir \"${idir}\"" ".param set @odir \"${odir}\"" ".read \"${srcdir}/test/test003-write.sql\"" > "${olog}"

cat "${olog}"

if grep -q FAILED "${odir}/test003-write.sql.log" ; then
	# exit with failure if at least one test has FAILED
	exit 1
else
	# no tests are FAILED, they were either PASSED or SKIPPED
	exit 0
fi
