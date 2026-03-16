void TSVConnShutdown ( TSVConn connp , int read , int write ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( connp ) == TS_SUCCESS ) ;
 VConnection * vc = ( VConnection * ) connp ;
 if ( read && write ) {
 vc -> do_io_shutdown ( IO_SHUTDOWN_READWRITE ) ;
 }
 else if ( read ) {
 vc -> do_io_shutdown ( IO_SHUTDOWN_READ ) ;
 }
 else if ( write ) {
 vc -> do_io_shutdown ( IO_SHUTDOWN_WRITE ) ;
 }
 }