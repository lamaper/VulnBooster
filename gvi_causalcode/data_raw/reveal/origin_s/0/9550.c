static void virtio_net_vhost_status ( VirtIONet * n , uint8_t status ) {
 if ( ! n -> nic -> nc . peer ) {
 return ;
 }
 if ( n -> nic -> nc . peer -> info -> type != NET_CLIENT_TYPE_TAP ) {
 return ;
 }
 if ( ! tap_get_vhost_net ( n -> nic -> nc . peer ) ) {
 return ;
 }
 if ( ! ! n -> vhost_started == virtio_net_started ( n , status ) && ! n -> nic -> nc . peer -> link_down ) {
 return ;
 }
 if ( ! n -> vhost_started ) {
 int r ;
 if ( ! vhost_net_query ( tap_get_vhost_net ( n -> nic -> nc . peer ) , & n -> vdev ) ) {
 return ;
 }
 r = vhost_net_start ( tap_get_vhost_net ( n -> nic -> nc . peer ) , & n -> vdev ) ;
 if ( r < 0 ) {
 error_report ( "unable to start vhost net: %d: " "falling back on userspace virtio" , - r ) ;
 }
 else {
 n -> vhost_started = 1 ;
 }
 }
 else {
 vhost_net_stop ( tap_get_vhost_net ( n -> nic -> nc . peer ) , & n -> vdev ) ;
 n -> vhost_started = 0 ;
 }
 }