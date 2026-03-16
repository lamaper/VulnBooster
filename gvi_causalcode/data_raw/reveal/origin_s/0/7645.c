void TSVConnAbort ( TSVConn connp , int error ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( connp ) == TS_SUCCESS ) ;
 VConnection * vc = ( VConnection * ) connp ;
 vc -> do_io_close ( error ) ;
 }