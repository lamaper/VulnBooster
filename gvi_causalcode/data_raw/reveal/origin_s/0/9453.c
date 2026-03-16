static gboolean qio_channel_websock_source_dispatch ( GSource * source , GSourceFunc callback , gpointer user_data ) {
 QIOChannelFunc func = ( QIOChannelFunc ) callback ;
 QIOChannelWebsockSource * wsource = ( QIOChannelWebsockSource * ) source ;
 return ( * func ) ( QIO_CHANNEL ( wsource -> wioc ) , qio_channel_websock_source_check ( source ) , user_data ) ;
 }