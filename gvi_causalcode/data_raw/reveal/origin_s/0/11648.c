static int qio_channel_websock_set_blocking ( QIOChannel * ioc , bool enabled , Error * * errp ) {
 QIOChannelWebsock * wioc = QIO_CHANNEL_WEBSOCK ( ioc ) ;
 qio_channel_set_blocking ( wioc -> master , enabled , errp ) ;
 return 0 ;
 }