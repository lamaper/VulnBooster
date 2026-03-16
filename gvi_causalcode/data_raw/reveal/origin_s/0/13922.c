void TSVConnActiveTimeoutSet ( TSVConn connp , TSHRTime timeout ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( connp ) == TS_SUCCESS ) ;
 NetVConnection * vc = ( NetVConnection * ) connp ;
 vc -> set_active_timeout ( timeout ) ;
 }