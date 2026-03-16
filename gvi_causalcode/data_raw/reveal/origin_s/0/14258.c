static int peer_has_vnet_hdr ( VirtIONet * n ) {
 if ( ! n -> nic -> nc . peer ) return 0 ;
 if ( n -> nic -> nc . peer -> info -> type != NET_CLIENT_TYPE_TAP ) return 0 ;
 n -> has_vnet_hdr = tap_has_vnet_hdr ( n -> nic -> nc . peer ) ;
 return n -> has_vnet_hdr ;
 }