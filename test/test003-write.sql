-- -*- coding: utf-8 -*-

.mode columns
.headers off
.nullvalue 'NULL'

.mode table

.width 86 32 32

select testname, expected, observed,
case when observed = 'SKIPPED' then 'SKIPPED' when expected = observed then 'PASSED' else 'FAILED' end as result
from (
	select 'file_mkdir(@odir||''/testdir-città'')' as testname,             'OK' as expected,   file_mkdir(@odir||'/testdir-città') as observed
	union all
	select 'file_mkdir(@odir||''/testdir/blà/città'')' as testname,         'OK' as expected,   file_mkdir(@odir||'/testdir/blà/città') as observed
	union all
	select 'file_to_file(@idir||''/test-città.png'', @odir||''/file_to_file_existing_dir/sì.png'')' as testname,
		'OK' as expected,
		file_to_file(@idir||'/test-città.png', @odir||'/file_to_file_existing_dir/sì.png') as observed
	union all
	select 'file_crc32(@odir||''/file_to_file_existing_dir/sì.png'')' as testname,   '9D14BE41' as expected,   file_crc32(@odir||'/file_to_file_existing_dir/sì.png') as observed
)
