static int peer_has_ufo ( VirtIONet * n ) {
 if ( ! peer_has_vnet_hdr ( n ) ) return 0 ;
 n -> has_ufo = tap_has_ufo ( n -> nic -> nc . peer ) ;
 return n -> has_ufo ;
 }