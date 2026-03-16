static void qio_channel_websock_flush_free ( gpointer user_data ) {
 QIOChannelWebsock * wioc = QIO_CHANNEL_WEBSOCK ( user_data ) ;
 object_unref ( OBJECT ( wioc ) ) ;
 }