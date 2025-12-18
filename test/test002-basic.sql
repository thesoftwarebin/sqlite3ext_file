-- -*- coding: utf-8 -*-

.mode columns
.headers off
.nullvalue 'NULL'

.load "../src/.libs/sqlite3ext_file-1.dll"

.mode box

.width 36 32 32

select testname, expected, observed,
case when observed = 'SKIPPED' then 'SKIPPED' when expected = observed then 'PASSED' else 'FAILED' end as result
from (
	select 'file_exists(''test.jpg'')' as testname,               'true' as expected,   file_exists('test.jpg') as observed
	union all
	select 'file_size(''test.jpg'')' as testname,              '2528271' as expected,   file_size('test.jpg') as observed
	union all
	select 'file_extension(''test.jpg'')' as testname,            '.jpg' as expected,   file_extension('test.jpg') as observed
	union all
	select 'file_extension(''città.jpg'')' as testname,           '.jpg' as expected,   file_extension('città.jpg') as observed
	union all
	select 'file_basename(''test.jpg'')' as testname,             'test' as expected,   file_basename('test.jpg') as observed
	union all
	select 'file_basename(''../test/test.jpg'')' as testname,     'test' as expected,   file_basename('../test/test.jpg') as observed
	union all
	select 'file_filename(''test.jpg'')' as testname,         'test.jpg' as expected,   file_filename('test.jpg') as observed
	union all
	select 'file_filename(''../test/test.jpg'')' as testname, 'test.jpg' as expected,   file_filename('../test/test.jpg') as observed
	union all
	select 'file_crc32(''test.jpg'')' as testname,            '146C516F' as expected,   file_crc32('test.jpg') as observed
	union all
	select 'file_crc32(''20250322_174419.jpg'')' as testname, '44888EE1' as expected,   file_crc32('20250322_174419.jpg') as observed
	union all
	select 'file_exists(''test-citta.png'')' as testname,         'true' as expected,   file_exists('test-citta.png') as observed
	union all
	select 'file_exists(''test-città.png'')' as testname,         'true' as expected,   file_exists('test-città.png') as observed
	union all
	select 'file_size(''test-citta.png'')' as testname,           '1345' as expected,   file_size('test-citta.png') as observed
	union all
	select 'file_size(''test-città.png'')' as testname,           '1345' as expected,   file_size('test-città.png') as observed
	union all
	select 'file_crc32(''test-citta.png'')' as testname,      '9D14BE41' as expected,   file_crc32('test-citta.png') as observed
	union all
	select 'file_crc32(''test-città.png'')' as testname,      '9D14BE41' as expected,   file_crc32('test-città.png') as observed
	union all
	select 'file_date_modified(''test-città.png'')' as testname, 
	                                               '2025-11-26 23:55:38' as expected,   file_date_modified('test-città.png') as observed
);
