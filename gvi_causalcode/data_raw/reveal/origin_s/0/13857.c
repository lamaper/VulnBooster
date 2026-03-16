void qio_channel_websock_handshake ( QIOChannelWebsock * ioc , QIOTaskFunc func , gpointer opaque , GDestroyNotify destroy ) {
 QIOTask * task ;
 task = qio_task_new ( OBJECT ( ioc ) , func , opaque , destroy ) ;
 trace_qio_channel_websock_handshake_start ( ioc ) ;
 trace_qio_channel_websock_handshake_pending ( ioc , G_IO_IN ) ;
 qio_channel_add_watch ( ioc -> master , G_IO_IN , qio_channel_websock_handshake_io , task , NULL ) ;
 }