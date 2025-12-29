if [ ! -f test/test004-bigfile.sql ] ; then exit 1 ; fi

rm -vrf test/inputdata/testbig.bin test/output/testdirbig

mkdir -p test/output/testdirbig

yes "mydata" | dd of=test/inputdata/testbig.bin bs=1M count=5678 iflag=fullblock

if (sqlite3.exe :memory: ".read test/test004-bigfile.sql" ".quit" | grep FAILED) ; then
	# exit with failure if at least one test has FAILED
	exit 1
else
	exit 0
fi	
