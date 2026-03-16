static void qemu_wait_io_event_common ( CPUState * cpu ) {
 if ( cpu -> stop ) {
 cpu -> stop = false ;
 cpu -> stopped = true ;
 qemu_cond_signal ( & qemu_pause_cond ) ;
 }
 flush_queued_work ( cpu ) ;
 cpu -> thread_kicked = false ;
 }