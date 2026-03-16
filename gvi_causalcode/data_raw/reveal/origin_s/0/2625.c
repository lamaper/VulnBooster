int qemuAgentGetInterfaces ( qemuAgentPtr mon , virDomainInterfacePtr * * ifaces ) {
 int ret = - 1 ;
 size_t i , j ;
 ssize_t size = - 1 ;
 virJSONValuePtr cmd = NULL ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr ret_array = NULL ;
 size_t ifaces_count = 0 ;
 size_t addrs_count = 0 ;
 virDomainInterfacePtr * ifaces_ret = NULL ;
 virHashTablePtr ifaces_store = NULL ;
 char * * ifname = NULL ;
 if ( ! ( ifaces_store = virHashCreate ( ifaces_count , NULL ) ) ) {
 virHashFree ( ifaces_store ) ;
 return - 1 ;
 }
 if ( ! ( cmd = qemuAgentMakeCommand ( "guest-network-get-interfaces" , NULL ) ) ) goto cleanup ;
 if ( qemuAgentCommand ( mon , cmd , & reply , false , VIR_DOMAIN_QEMU_AGENT_COMMAND_BLOCK ) < 0 || qemuAgentCheckError ( cmd , reply ) < 0 ) {
 goto cleanup ;
 }
 if ( ! ( ret_array = virJSONValueObjectGet ( reply , "return" ) ) ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "qemu agent didn't provide 'return' field" ) ) ;
 goto cleanup ;
 }
 if ( ( size = virJSONValueArraySize ( ret_array ) ) < 0 ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "qemu agent didn't return an array of interfaces" ) ) ;
 goto cleanup ;
 }
 for ( i = 0 ;
 i < size ;
 i ++ ) {
 virJSONValuePtr tmp_iface = virJSONValueArrayGet ( ret_array , i ) ;
 virJSONValuePtr ip_addr_arr = NULL ;
 const char * hwaddr , * ifname_s , * name = NULL ;
 ssize_t ip_addr_arr_size ;
 virDomainInterfacePtr iface = NULL ;
 if ( ! tmp_iface ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "qemu agent reply missing interface entry in array" ) ) ;
 goto error ;
 }
 name = virJSONValueObjectGetString ( tmp_iface , "name" ) ;
 if ( ! name ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "qemu agent didn't provide 'name' field" ) ) ;
 goto error ;
 }
 ifname = virStringSplit ( name , ":" , 2 ) ;
 ifname_s = ifname [ 0 ] ;
 iface = virHashLookup ( ifaces_store , ifname_s ) ;
 if ( ! iface ) {
 if ( VIR_EXPAND_N ( ifaces_ret , ifaces_count , 1 ) < 0 ) goto error ;
 if ( VIR_ALLOC ( ifaces_ret [ ifaces_count - 1 ] ) < 0 ) goto error ;
 if ( virHashAddEntry ( ifaces_store , ifname_s , ifaces_ret [ ifaces_count - 1 ] ) < 0 ) goto error ;
 iface = ifaces_ret [ ifaces_count - 1 ] ;
 iface -> naddrs = 0 ;
 if ( VIR_STRDUP ( iface -> name , ifname_s ) < 0 ) goto error ;
 hwaddr = virJSONValueObjectGetString ( tmp_iface , "hardware-address" ) ;
 if ( VIR_STRDUP ( iface -> hwaddr , hwaddr ) < 0 ) goto error ;
 }
 virStringListFree ( ifname ) ;
 ip_addr_arr = virJSONValueObjectGet ( tmp_iface , "ip-addresses" ) ;
 if ( ! ip_addr_arr ) continue ;
 if ( ( ip_addr_arr_size = virJSONValueArraySize ( ip_addr_arr ) ) < 0 ) goto error ;
 addrs_count = iface -> naddrs ;
 for ( j = 0 ;
 j < ip_addr_arr_size ;
 j ++ ) {
 const char * type , * addr ;
 virJSONValuePtr ip_addr_obj = virJSONValueArrayGet ( ip_addr_arr , j ) ;
 virDomainIPAddressPtr ip_addr ;
 if ( VIR_EXPAND_N ( iface -> addrs , addrs_count , 1 ) < 0 ) goto error ;
 ip_addr = & iface -> addrs [ addrs_count - 1 ] ;
 if ( ! ip_addr_obj ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "qemu agent reply missing IP addr in array" ) ) ;
 goto error ;
 }
 type = virJSONValueObjectGetString ( ip_addr_obj , "ip-address-type" ) ;
 if ( ! type ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "qemu agent didn't provide 'ip-address-type'" " field for interface '%s'" ) , name ) ;
 goto error ;
 }
 else if ( STREQ ( type , "ipv4" ) ) {
 ip_addr -> type = VIR_IP_ADDR_TYPE_IPV4 ;
 }
 else if ( STREQ ( type , "ipv6" ) ) {
 ip_addr -> type = VIR_IP_ADDR_TYPE_IPV6 ;
 }
 else {
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unknown ip address type '%s'" ) , type ) ;
 goto error ;
 }
 addr = virJSONValueObjectGetString ( ip_addr_obj , "ip-address" ) ;
 if ( ! addr ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "qemu agent didn't provide 'ip-address'" " field for interface '%s'" ) , name ) ;
 goto error ;
 }
 if ( VIR_STRDUP ( ip_addr -> addr , addr ) < 0 ) goto error ;
 if ( virJSONValueObjectGetNumberUint ( ip_addr_obj , "prefix" , & ip_addr -> prefix ) < 0 ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "malformed 'prefix' field" ) ) ;
 goto error ;
 }
 }
 iface -> naddrs = addrs_count ;
 }
 VIR_STEAL_PTR ( * ifaces , ifaces_ret ) ;
 ret = ifaces_count ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 virHashFree ( ifaces_store ) ;
 return ret ;
 error : if ( ifaces_ret ) {
 for ( i = 0 ;
 i < ifaces_count ;
 i ++ ) virDomainInterfaceFree ( ifaces_ret [ i ] ) ;
 }
 VIR_FREE ( ifaces_ret ) ;
 virStringListFree ( ifname ) ;
 goto cleanup ;
 }