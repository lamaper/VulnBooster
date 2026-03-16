static int selinux_tun_dev_create ( void ) {
 u32 sid = current_sid ( ) ;
 return avc_has_perm ( sid , sid , SECCLASS_TUN_SOCKET , TUN_SOCKET__CREATE , NULL ) ;
 }