void TSVConnActiveTimeoutCancel ( TSVConn connp ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( connp ) == TS_SUCCESS ) ;
 NetVConnection * vc = ( NetVConnection * ) connp ;
 vc -> cancel_active_timeout ( ) ;
 }