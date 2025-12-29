if [ ! -f test/test002-basic.sql ] ; then exit 1 ; fi

# forcing an exact date-time on this peculiar file because modification date is later validated by a SQL test
touch -t 202511262355.38 test/inputdata/test-città.png 

if (sqlite3.exe :memory: ".read test/test002-basic.sql" ".quit" | grep FAILED) ; then
	# fail if at least one test has FAILED 
	exit 1
else
	# no tests are FAILED, they were either PASSED or SKIPPED 
	exit 0
fi
