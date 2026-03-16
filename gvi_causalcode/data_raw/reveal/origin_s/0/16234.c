void hmp_info_usernet ( Monitor * mon , const QDict * qdict ) {
 SlirpState * s ;
 QTAILQ_FOREACH ( s , & slirp_stacks , entry ) {
 int id ;
 bool got_vlan_id = net_hub_id_for_client ( & s -> nc , & id ) == 0 ;
 monitor_printf ( mon , "VLAN %d (%s):\n" , got_vlan_id ? id : - 1 , s -> nc . name ) ;
 slirp_connection_info ( s -> slirp , mon ) ;
 }
 }