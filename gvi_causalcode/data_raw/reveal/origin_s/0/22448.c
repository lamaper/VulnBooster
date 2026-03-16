static gboolean qio_channel_websock_source_prepare ( GSource * source , gint * timeout ) {
 * timeout = - 1 ;
 return qio_channel_websock_source_check ( source ) ;
 }