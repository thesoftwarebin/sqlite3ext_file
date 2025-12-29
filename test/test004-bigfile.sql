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
	select 'file_exists(''test/inputdata/testbig.bin'')' as testname,            'true' as expected,   file_exists('test/inputdata/testbig.bin') as observed
	union all
	select 'file_size(''test/inputdata/testbig.bin'')' as testname,          5953814528 as expected,   file_size('test/inputdata/testbig.bin') as observed
	union all
	select 'file_crc32(''test/inputdata/testbig.bin'')' as testname,         'EA713BA8' as expected,   file_crc32('test/inputdata/testbig.bin') as observed
	union all
	select 'file_to_file(''test/inputdata/testbig.bin'', ''test/output/testdirbig/testbig_copy.bin'')' as testname,
		'OK' as expected,
		file_to_file('test/inputdata/testbig.bin', 'test/output/testdirbig/testbig_copy.bin') as observed
	union all
	select 'file_crc32(''test/output/testdirbig/testbig_copy.bin'')' as testname,
		'EA713BA8' as expected,
		file_crc32('test/output/testdirbig/testbig_copy.bin') as observed
);
