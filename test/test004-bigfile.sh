if [ ! -f test/test004-bigfile.sql ] ; then exit 1 ; fi

rm -vrf test/testbig.bin
yes "mydata" | dd of=test/testbig.bin bs=1M count=5678 iflag=fullblock

if (cd test && sqlite3.exe :memory: ".read test004-bigfile.sql" ".quit" | grep FAILED) ; then
	# exit with failure if at least one test has FAILED
	exit 1
else
	exit 0
fi	
