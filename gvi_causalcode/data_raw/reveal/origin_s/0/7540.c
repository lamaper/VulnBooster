static int qio_channel_websock_close ( QIOChannel * ioc , Error * * errp ) {
 QIOChannelWebsock * wioc = QIO_CHANNEL_WEBSOCK ( ioc ) ;
 trace_qio_channel_websock_close ( ioc ) ;
 return qio_channel_close ( wioc -> master , errp ) ;
 }