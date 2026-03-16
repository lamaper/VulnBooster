QIOChannelWebsock * qio_channel_websock_new_server ( QIOChannel * master ) {
 QIOChannelWebsock * wioc ;
 QIOChannel * ioc ;
 wioc = QIO_CHANNEL_WEBSOCK ( object_new ( TYPE_QIO_CHANNEL_WEBSOCK ) ) ;
 ioc = QIO_CHANNEL ( wioc ) ;
 wioc -> master = master ;
 if ( qio_channel_has_feature ( master , QIO_CHANNEL_FEATURE_SHUTDOWN ) ) {
 qio_channel_set_feature ( ioc , QIO_CHANNEL_FEATURE_SHUTDOWN ) ;
 }
 object_ref ( OBJECT ( master ) ) ;
 trace_qio_channel_websock_new_server ( wioc , master ) ;
 return wioc ;
 }