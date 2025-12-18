if [ ! -f test/test002-basic.sql ] ; then exit 1 ; fi


if (cd test && sqlite3.exe :memory: ".read test002-basic.sql" ".quit" | grep FAILED) ; then
	# fail if at least one test has FAILED 
	exit 1
else
	# no tests are FAILED, they were either PASSED or SKIPPED 
	exit 0
fi
