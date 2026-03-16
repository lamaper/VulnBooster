static void qio_channel_websock_source_finalize ( GSource * source ) {
 QIOChannelWebsockSource * ssource = ( QIOChannelWebsockSource * ) source ;
 object_unref ( OBJECT ( ssource -> wioc ) ) ;
 }