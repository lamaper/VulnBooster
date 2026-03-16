static unsigned virtio_s390_get_features ( void * opaque ) {
 VirtIOS390Device * dev = ( VirtIOS390Device * ) opaque ;
 return dev -> host_features ;
 }