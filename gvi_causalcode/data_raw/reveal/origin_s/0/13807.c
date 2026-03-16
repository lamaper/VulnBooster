static void qio_channel_websock_encode ( QIOChannelWebsock * ioc ) {
 if ( ! ioc -> rawoutput . offset ) {
 return ;
 }
 qio_channel_websock_encode_buffer ( ioc , & ioc -> encoutput , QIO_CHANNEL_WEBSOCK_OPCODE_BINARY_FRAME , & ioc -> rawoutput ) ;
 buffer_reset ( & ioc -> rawoutput ) ;
 }