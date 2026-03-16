static void cpu_handle_guest_debug ( CPUState * cpu ) {
 gdb_set_stop_cpu ( cpu ) ;
 qemu_system_debug_request ( ) ;
 cpu -> stopped = true ;
 }