if [ ! -f test/test003-write.sql ] ; then exit 1 ; fi

rm -vrf test/testdir test/testdir-città

if (cd test && sqlite3.exe :memory: ".read test003-write.sql" ".quit" | grep FAILED) ; then
	# exit with failure if at least one test has FAILED
	exit 1
else
	# no tests are FAILED, they were either PASSED or SKIPPED
	exit 0
fi
