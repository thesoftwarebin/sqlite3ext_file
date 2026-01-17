SUBDIRS = src 

if HAVESQLITE3SHELLFORTESTS

EXTRA_DIST = \
	test/test001-sqlite3.sh                          \
	test/test002-basic.sh test/test002-basic.sql     \
	test/test003-write.sh test/test003-write.sql     \
	test/test004-bigfile.sh test/test004-bigfile.sql \
	test/inputdata/20231030_150218.jpg               \
	test/inputdata/test-citta.png                    \
	test/inputdata/test-città.png                    \
	test/inputdata/test-modified-date.png            \
	.gitignore

TESTS = test/test001-sqlite3.sh test/test002-basic.sh test/test003-write.sh test/test004-bigfile.sh

if HAVEBIGFILETESTS
AM_TESTS_ENVIRONMENT = \
	export havebigtestfiles=true \
	;
endif

endif

CLEANFILES = test/inputdata/testbig.bin

clean-local:
	-rm -vrf test/test002-output test/test003-output test/test004-output
