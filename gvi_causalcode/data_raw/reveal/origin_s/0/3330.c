static void nbd_update_server_watch ( void ) {
 if ( nbd_can_accept ( ) ) {
 if ( server_watch == - 1 ) {
 server_watch = qio_channel_add_watch ( QIO_CHANNEL ( server_ioc ) , G_IO_IN , nbd_accept , NULL , NULL ) ;
 }
 }
 else {
 if ( server_watch != - 1 ) {
 g_source_remove ( server_watch ) ;
 server_watch = - 1 ;
 }
 }
 }