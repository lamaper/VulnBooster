static int64_t qemu_icount_round ( int64_t count ) {
 return ( count + ( 1 << icount_time_shift ) - 1 ) >> icount_time_shift ;
 }