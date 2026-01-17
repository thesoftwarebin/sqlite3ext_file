-- -*- coding: utf-8 -*-

.mode columns
.headers off
.nullvalue 'NULL'

.mode table

.width 36 32 32

select testname, expected, observed,
case when observed = 'SKIPPED' then 'SKIPPED' when expected = observed then 'PASSED' else 'FAILED' end as result
from (
	select 'file_exists(@idir||''/testbig.bin'')' as testname,            'true' as expected,   file_exists(@idir||'/testbig.bin') as observed
	union all
	select 'file_size(@idir||''/testbig.bin'')' as testname,          5953814528 as expected,   file_size(@idir||'/testbig.bin') as observed
	union all
	select 'file_crc32(@idir||''/testbig.bin'')' as testname,         'EA713BA8' as expected,   file_crc32(@idir||'/testbig.bin') as observed
	union all
	select 'file_to_file(@idir||''/testbig.bin'', @odir||''/testbig_copy.bin'')' as testname,
		'OK' as expected,
		file_to_file(@idir||'/testbig.bin', @odir||'/testbig_copy.bin') as observed
	union all
	select 'file_crc32(@odir||''testbig_copy.bin'')' as testname,
		'EA713BA8' as expected,
		file_crc32(@odir||'/testbig_copy.bin') as observed
);
