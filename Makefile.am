SUBDIRS = src 

if HAVESQLITE3SHELLFORTESTS

if HAVEBIGFILETESTS
BIGTESTS = test/test004-bigfile.sh
else
BIGTESTS =
endif

EXTRA_DIST = \
	test/test001-sqlite3.sh                          \
	test/test002-basic.sh test/test002-basic.sql     \
	test/test003-write.sh test/test003-write.sql     \
	test/test004-bigfile.sh test/test004-bigfile.sql \
	test/inputdata/20231030_150218.jpg               \
	test/inputdata/test-citta.png                    \
	test/inputdata/test-città.png                    \
	.gitignore

TESTS = test/test001-sqlite3.sh test/test002-basic.sh test/test003-write.sh $(BIGTESTS)

endif

CLEANFILES = test/inputdata/testbig.bin

clean-local:
	-rm -rf test/output
