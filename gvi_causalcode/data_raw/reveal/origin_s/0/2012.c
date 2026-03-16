static void qio_channel_websock_unset_watch ( QIOChannelWebsock * ioc ) {
 if ( ioc -> io_tag ) {
 g_source_remove ( ioc -> io_tag ) ;
 ioc -> io_tag = 0 ;
 }
 }