int s390_virtio_hypercall ( CPUState * env ) {
 int r = 0 , i ;
 target_ulong mem = env -> regs [ 2 ] ;
 dprintf ( "KVM hypercall: %ld\n" , env -> regs [ 1 ] ) ;
 switch ( env -> regs [ 1 ] ) {
 case KVM_S390_VIRTIO_NOTIFY : if ( mem > ram_size ) {
 VirtIOS390Device * dev = s390_virtio_bus_find_vring ( s390_bus , mem , & i ) ;
 if ( dev ) {
 virtio_queue_notify ( dev -> vdev , i ) ;
 }
 else {
 r = - EINVAL ;
 }
 }
 else {
 }
 break ;
 case KVM_S390_VIRTIO_RESET : {
 break ;
 }
 case KVM_S390_VIRTIO_SET_STATUS : {
 VirtIOS390Device * dev ;
 dev = s390_virtio_bus_find_mem ( s390_bus , mem ) ;
 if ( dev ) {
 s390_virtio_device_update_status ( dev ) ;
 }
 else {
 r = - EINVAL ;
 }
 break ;
 }
 default : r = - EINVAL ;
 break ;
 }
 env -> regs [ 2 ] = r ;
 return 0 ;
 }