int64_t cpu_get_icount ( void ) {
 int64_t icount ;
 CPUArchState * env = cpu_single_env ;
 icount = qemu_icount ;
 if ( env ) {
 if ( ! can_do_io ( env ) ) {
 fprintf ( stderr , "Bad clock read\n" ) ;
 }
 icount -= ( env -> icount_decr . u16 . low + env -> icount_extra ) ;
 }
 return qemu_icount_bias + ( icount << icount_time_shift ) ;
 }