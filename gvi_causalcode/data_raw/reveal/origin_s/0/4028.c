static void qio_channel_websock_set_cork ( QIOChannel * ioc , bool enabled ) {
 QIOChannelWebsock * tioc = QIO_CHANNEL_WEBSOCK ( ioc ) ;
 qio_channel_set_cork ( tioc -> master , enabled ) ;
 }