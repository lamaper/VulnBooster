static void icount_adjust ( void ) {
 int64_t cur_time ;
 int64_t cur_icount ;
 int64_t delta ;
 static int64_t last_delta ;
 if ( ! runstate_is_running ( ) ) {
 return ;
 }
 cur_time = cpu_get_clock ( ) ;
 cur_icount = qemu_get_clock_ns ( vm_clock ) ;
 delta = cur_icount - cur_time ;
 if ( delta > 0 && last_delta + ICOUNT_WOBBLE < delta * 2 && icount_time_shift > 0 ) {
 icount_time_shift -- ;
 }
 if ( delta < 0 && last_delta - ICOUNT_WOBBLE > delta * 2 && icount_time_shift < MAX_ICOUNT_SHIFT ) {
 icount_time_shift ++ ;
 }
 last_delta = delta ;
 qemu_icount_bias = cur_icount - ( qemu_icount << icount_time_shift ) ;
 }