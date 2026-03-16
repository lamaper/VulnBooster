void qdev_set_nic_properties ( DeviceState * dev , NICInfo * nd ) {
 qdev_prop_set_macaddr ( dev , "mac" , nd -> macaddr ) ;
 if ( nd -> vlan ) qdev_prop_set_vlan ( dev , "vlan" , nd -> vlan ) ;
 if ( nd -> netdev ) qdev_prop_set_netdev ( dev , "netdev" , nd -> netdev ) ;
 if ( nd -> nvectors != NIC_NVECTORS_UNSPECIFIED && qdev_prop_exists ( dev , "vectors" ) ) {
 qdev_prop_set_uint32 ( dev , "vectors" , nd -> nvectors ) ;
 }
 }