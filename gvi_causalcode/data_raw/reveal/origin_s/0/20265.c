static gboolean qio_channel_websock_flush ( QIOChannel * ioc , GIOCondition condition , gpointer user_data ) {
 QIOChannelWebsock * wioc = QIO_CHANNEL_WEBSOCK ( user_data ) ;
 ssize_t ret ;
 if ( condition & G_IO_OUT ) {
 ret = qio_channel_websock_write_wire ( wioc , & wioc -> io_err ) ;
 if ( ret < 0 ) {
 goto cleanup ;
 }
 }
 if ( condition & G_IO_IN ) {
 ret = qio_channel_websock_read_wire ( wioc , & wioc -> io_err ) ;
 if ( ret < 0 ) {
 goto cleanup ;
 }
 }
 cleanup : qio_channel_websock_set_watch ( wioc ) ;
 return FALSE ;
 }