int TSHttpSsnIsInternal ( TSHttpSsn ssnp ) {
 ProxyClientSession * cs = reinterpret_cast < ProxyClientSession * > ( ssnp ) ;
 if ( ! cs ) {
 return 0 ;
 }
 NetVConnection * vc = cs -> get_netvc ( ) ;
 if ( ! vc ) {
 return 0 ;
 }
 return vc -> get_is_internal_request ( ) ? 1 : 0 ;
 }