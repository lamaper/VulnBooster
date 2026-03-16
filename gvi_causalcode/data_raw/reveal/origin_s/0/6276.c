static int qio_channel_websock_shutdown ( QIOChannel * ioc , QIOChannelShutdown how , Error * * errp ) {
 QIOChannelWebsock * tioc = QIO_CHANNEL_WEBSOCK ( ioc ) ;
 return qio_channel_shutdown ( tioc -> master , how , errp ) ;
 }