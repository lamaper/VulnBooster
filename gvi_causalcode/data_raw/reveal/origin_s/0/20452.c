static SlirpState * slirp_lookup ( Monitor * mon , const char * vlan , const char * stack ) {
 if ( vlan ) {
 NetClientState * nc ;
 nc = net_hub_find_client_by_name ( strtol ( vlan , NULL , 0 ) , stack ) ;
 if ( ! nc ) {
 monitor_printf ( mon , "unrecognized (vlan-id, stackname) pair\n" ) ;
 return NULL ;
 }
 if ( strcmp ( nc -> model , "user" ) ) {
 monitor_printf ( mon , "invalid device specified\n" ) ;
 return NULL ;
 }
 return DO_UPCAST ( SlirpState , nc , nc ) ;
 }
 else {
 if ( QTAILQ_EMPTY ( & slirp_stacks ) ) {
 monitor_printf ( mon , "user mode network stack not in use\n" ) ;
 return NULL ;
 }
 return QTAILQ_FIRST ( & slirp_stacks ) ;
 }
 }