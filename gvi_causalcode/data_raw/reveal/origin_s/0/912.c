static void tcg_handle_interrupt ( CPUState * cpu , int mask ) {
 CPUArchState * env = cpu -> env_ptr ;
 int old_mask ;
 old_mask = cpu -> interrupt_request ;
 cpu -> interrupt_request |= mask ;
 if ( ! qemu_cpu_is_self ( cpu ) ) {
 qemu_cpu_kick ( cpu ) ;
 return ;
 }
 if ( use_icount ) {
 env -> icount_decr . u16 . high = 0xffff ;
 if ( ! can_do_io ( env ) && ( mask & ~ old_mask ) != 0 ) {
 cpu_abort ( env , "Raised interrupt while not in I/O function" ) ;
 }
 }
 else {
 cpu -> tcg_exit_req = 1 ;
 }
 }