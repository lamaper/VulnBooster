static void icount_adjust_vm ( void * opaque ) {
 qemu_mod_timer ( icount_vm_timer , qemu_get_clock_ns ( vm_clock ) + get_ticks_per_sec ( ) / 10 ) ;
 icount_adjust ( ) ;
 }