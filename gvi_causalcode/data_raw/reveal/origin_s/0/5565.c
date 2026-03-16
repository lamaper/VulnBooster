void qtest_clock_warp ( int64_t dest ) {
 int64_t clock = qemu_get_clock_ns ( vm_clock ) ;
 assert ( qtest_enabled ( ) ) ;
 while ( clock < dest ) {
 int64_t deadline = qemu_clock_deadline ( vm_clock ) ;
 int64_t warp = MIN ( dest - clock , deadline ) ;
 qemu_icount_bias += warp ;
 qemu_run_timers ( vm_clock ) ;
 clock = qemu_get_clock_ns ( vm_clock ) ;
 }
 qemu_notify_event ( ) ;
 }