int64_t cpu_get_icount ( void ) {
 int64_t icount ;
 CPUState * cpu = current_cpu ;
 icount = qemu_icount ;
 if ( cpu ) {
 CPUArchState * env = cpu -> env_ptr ;
 if ( ! can_do_io ( env ) ) {
 fprintf ( stderr , "Bad clock read\n" ) ;
 }
 icount -= ( env -> icount_decr . u16 . low + env -> icount_extra ) ;
 }
 return qemu_icount_bias + ( icount << icount_time_shift ) ;
 }