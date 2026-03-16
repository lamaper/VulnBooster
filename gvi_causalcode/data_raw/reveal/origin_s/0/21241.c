static void virtio_net_reset ( VirtIODevice * vdev ) {
 VirtIONet * n = to_virtio_net ( vdev ) ;
 n -> promisc = 1 ;
 n -> allmulti = 0 ;
 n -> alluni = 0 ;
 n -> nomulti = 0 ;
 n -> nouni = 0 ;
 n -> nobcast = 0 ;
 n -> mac_table . in_use = 0 ;
 n -> mac_table . first_multi = 0 ;
 n -> mac_table . multi_overflow = 0 ;
 n -> mac_table . uni_overflow = 0 ;
 memset ( n -> mac_table . macs , 0 , MAC_TABLE_ENTRIES * ETH_ALEN ) ;
 memset ( n -> vlans , 0 , MAX_VLAN >> 3 ) ;
 }