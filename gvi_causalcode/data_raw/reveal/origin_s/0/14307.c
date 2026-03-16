void TSVConnClose ( TSVConn connp ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( connp ) == TS_SUCCESS ) ;
 VConnection * vc = ( VConnection * ) connp ;
 vc -> do_io_close ( ) ;
 }