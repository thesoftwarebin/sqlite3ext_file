# -*- coding: utf-8 -*-

if [ ! -f "${srcdir}/test/test004-bigfile.sql" ] ; then exit 99 ; fi

if [ -f "./src/.libs/sqlite3ext_file-1.dll" ] ; then
	libtotest="./src/.libs/sqlite3ext_file-1.dll"
elif [ -f "./src/.libs/sqlite3ext_file.so.1" ] ; then
	libtotest="./src/.libs/sqlite3ext_file.so.1"
else
	echo "error: cannot find the binary library to test (so or .dll file)"
	exit 99
fi

if [ "${havebigtestfiles}" != "true" ] ; then echo havebigtestfiles=${havebigtestfiles} ; exit 77 ; fi   # exit code 77 means "skip"

idir="${srcdir}/test/inputdata"
odir="./test/test004-output"

olog="${odir}/test004-bigfile.sql.log"

rm -vrf "${idir}/testbig.bin" "${odir}"

mkdir -p "${odir}"

yes "mydata" | dd of="${idir}/testbig.bin" bs=1M count=5678 iflag=fullblock

sqlite3 :memory: ".load \"${libtotest}\"" ".param init" ".param set @idir \"${idir}\"" ".param set @odir \"${odir}\"" ".read \"${srcdir}/test/test004-bigfile.sql\"" > "${olog}"

cat "${olog}"

if grep FAILED "${olog}" ; then
	# exit with failure if at least one test has FAILED
	exit 1
else
	exit 0
fi
