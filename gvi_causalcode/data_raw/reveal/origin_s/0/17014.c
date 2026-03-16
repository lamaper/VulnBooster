static void qio_channel_websock_class_init ( ObjectClass * klass , void * class_data G_GNUC_UNUSED ) {
 QIOChannelClass * ioc_klass = QIO_CHANNEL_CLASS ( klass ) ;
 ioc_klass -> io_writev = qio_channel_websock_writev ;
 ioc_klass -> io_readv = qio_channel_websock_readv ;
 ioc_klass -> io_set_blocking = qio_channel_websock_set_blocking ;
 ioc_klass -> io_set_cork = qio_channel_websock_set_cork ;
 ioc_klass -> io_set_delay = qio_channel_websock_set_delay ;
 ioc_klass -> io_close = qio_channel_websock_close ;
 ioc_klass -> io_shutdown = qio_channel_websock_shutdown ;
 ioc_klass -> io_create_watch = qio_channel_websock_create_watch ;
 }