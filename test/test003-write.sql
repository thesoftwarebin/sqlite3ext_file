-- -*- coding: utf-8 -*-

.mode columns
.headers off
.nullvalue 'NULL'

.load "src/.libs/sqlite3ext_file-1.dll"

.mode box

.width 36 32 32

select testname, expected, observed,
case when observed = 'SKIPPED' then 'SKIPPED' when expected = observed then 'PASSED' else 'FAILED' end as result
from (
	select 'file_mkdir(''test/output/testdir-città'')' as testname,             'OK' as expected,   file_mkdir('test/output/testdir-città') as observed
	union all
	select 'file_mkdir(''test/output/testdir/blà/città'')' as testname,         'OK' as expected,   file_mkdir('test/output/testdir/blà/città') as observed
	union all
	select 'file_to_file(''test/inputdata/test-città.png'', ''test/output/filetofile_sì/sì.png'')' as testname,
		'OK' as expected,
		file_to_file('test/inputdata/test-città.png', 'test/output/filetofile_sì/sì.png') as observed
	union all
	select 'file_crc32(''test/output/filetofile_sì/sì.png'')' as testname,   '9D14BE41' as expected,   file_crc32('test/output/filetofile_sì/sì.png') as observed
);
