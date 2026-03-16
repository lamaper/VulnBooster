static void qio_channel_websock_set_watch ( QIOChannelWebsock * ioc ) {
 GIOCondition cond = 0 ;
 qio_channel_websock_unset_watch ( ioc ) ;
 if ( ioc -> io_err ) {
 return ;
 }
 if ( ioc -> encoutput . offset || ioc -> ping_reply . offset ) {
 cond |= G_IO_OUT ;
 }
 if ( ioc -> encinput . offset < QIO_CHANNEL_WEBSOCK_MAX_BUFFER && ! ioc -> io_eof ) {
 cond |= G_IO_IN ;
 }
 if ( cond ) {
 object_ref ( OBJECT ( ioc ) ) ;
 ioc -> io_tag = qio_channel_add_watch ( ioc -> master , cond , qio_channel_websock_flush , ioc , qio_channel_websock_flush_free ) ;
 }
 }