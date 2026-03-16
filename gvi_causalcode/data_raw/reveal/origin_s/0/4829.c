void qemu_clock_warp ( QEMUClock * clock ) {
 int64_t deadline ;
 if ( clock != vm_clock || ! use_icount ) {
 return ;
 }
 icount_warp_rt ( NULL ) ;
 if ( ! all_cpu_threads_idle ( ) || ! qemu_clock_has_timers ( vm_clock ) ) {
 qemu_del_timer ( icount_warp_timer ) ;
 return ;
 }
 if ( qtest_enabled ( ) ) {
 return ;
 }
 vm_clock_warp_start = qemu_get_clock_ns ( rt_clock ) ;
 deadline = qemu_clock_deadline ( vm_clock ) ;
 if ( deadline > 0 ) {
 qemu_mod_timer ( icount_warp_timer , vm_clock_warp_start + deadline ) ;
 }
 else {
 qemu_notify_event ( ) ;
 }
 }