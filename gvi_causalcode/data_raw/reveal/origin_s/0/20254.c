static void virtio_net_set_status ( struct VirtIODevice * vdev , uint8_t status ) {
 VirtIONet * n = to_virtio_net ( vdev ) ;
 virtio_net_vhost_status ( n , status ) ;
 if ( ! n -> tx_waiting ) {
 return ;
 }
 if ( virtio_net_started ( n , status ) && ! n -> vhost_started ) {
 if ( n -> tx_timer ) {
 qemu_mod_timer ( n -> tx_timer , qemu_get_clock_ns ( vm_clock ) + n -> tx_timeout ) ;
 }
 else {
 qemu_bh_schedule ( n -> tx_bh ) ;
 }
 }
 else {
 if ( n -> tx_timer ) {
 qemu_del_timer ( n -> tx_timer ) ;
 }
 else {
 qemu_bh_cancel ( n -> tx_bh ) ;
 }
 }
 }