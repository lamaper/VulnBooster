static void icount_warp_rt ( void * opaque ) {
 if ( vm_clock_warp_start == - 1 ) {
 return ;
 }
 if ( runstate_is_running ( ) ) {
 int64_t clock = qemu_get_clock_ns ( rt_clock ) ;
 int64_t warp_delta = clock - vm_clock_warp_start ;
 if ( use_icount == 1 ) {
 qemu_icount_bias += warp_delta ;
 }
 else {
 int64_t cur_time = cpu_get_clock ( ) ;
 int64_t cur_icount = qemu_get_clock_ns ( vm_clock ) ;
 int64_t delta = cur_time - cur_icount ;
 qemu_icount_bias += MIN ( warp_delta , delta ) ;
 }
 if ( qemu_clock_expired ( vm_clock ) ) {
 qemu_notify_event ( ) ;
 }
 }
 vm_clock_warp_start = - 1 ;
 }