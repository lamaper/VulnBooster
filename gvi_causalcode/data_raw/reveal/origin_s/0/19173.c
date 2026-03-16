static gboolean qio_channel_websock_handshake_io ( QIOChannel * ioc , GIOCondition condition , gpointer user_data ) {
 QIOTask * task = user_data ;
 QIOChannelWebsock * wioc = QIO_CHANNEL_WEBSOCK ( qio_task_get_source ( task ) ) ;
 Error * err = NULL ;
 int ret ;
 ret = qio_channel_websock_handshake_read ( wioc , & err ) ;
 if ( ret < 0 ) {
 trace_qio_channel_websock_handshake_fail ( ioc , error_get_pretty ( err ) ) ;
 qio_task_set_error ( task , err ) ;
 qio_task_complete ( task ) ;
 return FALSE ;
 }
 if ( ret == 0 ) {
 trace_qio_channel_websock_handshake_pending ( ioc , G_IO_IN ) ;
 return TRUE ;
 }
 if ( err ) {
 error_propagate ( & wioc -> io_err , err ) ;
 }
 trace_qio_channel_websock_handshake_reply ( ioc ) ;
 qio_channel_add_watch ( wioc -> master , G_IO_OUT , qio_channel_websock_handshake_send , task , NULL ) ;
 return FALSE ;
 }