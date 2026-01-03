-- -*- coding: utf-8 -*-

.mode columns
.headers off
.nullvalue 'NULL'

.mode box

.width 64 32 24

select testname, expected, observed,
case when observed = 'SKIPPED' then 'SKIPPED' when expected = observed then 'PASSED' else 'FAILED' end as result
from (
	select 'file_exists(@idir||''/20231030_150218.jpg'')' as testname,            'true' as expected,                file_exists(@idir||'/20231030_150218.jpg') as observed
	union all
	select 'file_size(@idir||''/20231030_150218.jpg'')' as testname,              1011865 as expected,               file_size(@idir||'/20231030_150218.jpg') as observed
	union all
	select 'file_extension(@idir||''/20231030_150218.jpg'')' as testname,         '.jpg' as expected,                file_extension(@idir||'/20231030_150218.jpg') as observed
	union all
	select 'file_extension(@idir||''/città.jpg'')' as testname,                   '.jpg' as expected,                file_extension(@idir||'/città.jpg') as observed
	union all
	select 'file_basename(@idir||''/20231030_150218.jpg'')' as testname,          '20231030_150218' as expected,     file_basename(@idir||'/20231030_150218.jpg') as observed
	union all
	select 'file_basename(@idir||''/../test/inputdata/20231030_150218.jpg'')' as testname,  '20231030_150218' as expected,     file_basename(@idir||'/../test/inputdata/20231030_150218.jpg') as observed
	union all
	select 'file_filename(@idir||''/20231030_150218.jpg'')' as testname,          '20231030_150218.jpg' as expected, file_filename(@idir||'/20231030_150218.jpg') as observed
	union all
	select 'file_filename(@idir||''/../test/inputdata/20231030_150218.jpg'')' as testname,  '20231030_150218.jpg' as expected, file_filename(@idir||'/../test/inputdata/20231030_150218.jpg') as observed
	union all
	select 'file_crc32(@idir||''/20231030_150218.jpg'')' as testname,             '1E4F7DE5' as expected,            file_crc32(@idir||'/20231030_150218.jpg') as observed
	union all
	select 'file_exists(@idir||''/test-citta.png'')' as testname,                 'true' as expected,                file_exists(@idir||'/test-citta.png') as observed
	union all
	select 'file_exists(@idir||''/test-città.png'')' as testname,                 'true' as expected,                file_exists(@idir||'/test-città.png') as observed
	union all
	select 'file_size(@idir||''/test-citta.png'')' as testname,                   1345 as expected,                  file_size(@idir||'/test-citta.png') as observed
	union all
	select 'file_size(@idir||''/test-città.png'')' as testname,                   1345 as expected,                  file_size(@idir||'/test-città.png') as observed
	union all
	select 'file_crc32(@idir||''/test-citta.png'')' as testname,                  '9D14BE41' as expected,            file_crc32(@idir||'/test-citta.png') as observed
	union all
	select 'file_crc32(@idir||''/test-città.png'')' as testname,                  '9D14BE41' as expected,            file_crc32(@idir||'/test-città.png') as observed
	union all
	select 'file_date_modified(@idir||''/test-città.png'')' as testname,          '2025-11-26 23:55:38' as expected, file_date_modified(@idir||'/test-città.png') as observed
);
