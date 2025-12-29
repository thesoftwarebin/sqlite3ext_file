-- -*- coding: utf-8 -*-

.mode columns
.headers off
.nullvalue 'NULL'

.load "src/.libs/sqlite3ext_file-1.dll"

.mode box

.width 60 32 24

select testname, expected, observed,
case when observed = 'SKIPPED' then 'SKIPPED' when expected = observed then 'PASSED' else 'FAILED' end as result
from (
	select 'file_exists(''test/inputdata/20231030_150218.jpg'')' as testname,            'true' as expected,                file_exists('test/inputdata/20231030_150218.jpg') as observed
	union all
	select 'file_size(''test/inputdata/20231030_150218.jpg'')' as testname,              1011865 as expected,               file_size('test/inputdata/20231030_150218.jpg') as observed
	union all
	select 'file_extension(''test/inputdata/20231030_150218.jpg'')' as testname,         '.jpg' as expected,                file_extension('test/inputdata/20231030_150218.jpg') as observed
	union all
	select 'file_extension(''test/inputdata/città.jpg'')' as testname,                   '.jpg' as expected,                file_extension('test/inputdata/città.jpg') as observed
	union all
	select 'file_basename(''test/inputdata/20231030_150218.jpg'')' as testname,          '20231030_150218' as expected,     file_basename('test/inputdata/20231030_150218.jpg') as observed
	union all
	select 'file_basename(''test/../test/inputdata/20231030_150218.jpg'')' as testname,  '20231030_150218' as expected,     file_basename('test/../test/inputdata/20231030_150218.jpg') as observed
	union all
	select 'file_filename(''test/inputdata/20231030_150218.jpg'')' as testname,          '20231030_150218.jpg' as expected, file_filename('test/inputdata/20231030_150218.jpg') as observed
	union all
	select 'file_filename(''test/../test/inputdata/20231030_150218.jpg'')' as testname,  '20231030_150218.jpg' as expected, file_filename('test/../test/inputdata/20231030_150218.jpg') as observed
	union all
	select 'file_crc32(''test/inputdata/20231030_150218.jpg'')' as testname,             '1E4F7DE5' as expected,            file_crc32('test/inputdata/20231030_150218.jpg') as observed
	union all
	select 'file_exists(''test/inputdata/test-citta.png'')' as testname,                 'true' as expected,                file_exists('test/inputdata/test-citta.png') as observed
	union all
	select 'file_exists(''test/inputdata/test-città.png'')' as testname,                 'true' as expected,                file_exists('test/inputdata/test-città.png') as observed
	union all
	select 'file_size(''test/inputdata/test-citta.png'')' as testname,                   1345 as expected,                  file_size('test/inputdata/test-citta.png') as observed
	union all
	select 'file_size(''test/inputdata/test-città.png'')' as testname,                   1345 as expected,                  file_size('test/inputdata/test-città.png') as observed
	union all
	select 'file_crc32(''test/inputdata/test-citta.png'')' as testname,                  '9D14BE41' as expected,            file_crc32('test/inputdata/test-citta.png') as observed
	union all
	select 'file_crc32(''test/inputdata/test-città.png'')' as testname,                  '9D14BE41' as expected,            file_crc32('test/inputdata/test-città.png') as observed
	union all
	select 'file_date_modified(''test/inputdata/test-città.png'')' as testname,          '2025-11-26 23:55:38' as expected, file_date_modified('test/inputdata/test-città.png') as observed
);
