static void qio_channel_websock_set_delay ( QIOChannel * ioc , bool enabled ) {
 QIOChannelWebsock * tioc = QIO_CHANNEL_WEBSOCK ( ioc ) ;
 qio_channel_set_delay ( tioc -> master , enabled ) ;
 }