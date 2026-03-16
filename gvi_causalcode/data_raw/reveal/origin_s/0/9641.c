static GSource * qio_channel_websock_create_watch ( QIOChannel * ioc , GIOCondition condition ) {
 QIOChannelWebsock * wioc = QIO_CHANNEL_WEBSOCK ( ioc ) ;
 QIOChannelWebsockSource * ssource ;
 GSource * source ;
 source = g_source_new ( & qio_channel_websock_source_funcs , sizeof ( QIOChannelWebsockSource ) ) ;
 ssource = ( QIOChannelWebsockSource * ) source ;
 ssource -> wioc = wioc ;
 object_ref ( OBJECT ( wioc ) ) ;
 ssource -> condition = condition ;
 qio_channel_websock_set_watch ( wioc ) ;
 return source ;
 }