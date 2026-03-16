static int qio_channel_websock_decode_payload ( QIOChannelWebsock * ioc , Error * * errp ) {
 size_t i ;
 size_t payload_len = 0 ;
 uint32_t * payload32 ;
 if ( ioc -> payload_remain ) {
 if ( ioc -> encinput . offset < ioc -> payload_remain ) {
 if ( ioc -> opcode & QIO_CHANNEL_WEBSOCK_CONTROL_OPCODE_MASK ) {
 return QIO_CHANNEL_ERR_BLOCK ;
 }
 payload_len = ioc -> encinput . offset - ( ioc -> encinput . offset % 4 ) ;
 }
 else {
 payload_len = ioc -> payload_remain ;
 }
 if ( payload_len == 0 ) {
 return QIO_CHANNEL_ERR_BLOCK ;
 }
 ioc -> payload_remain -= payload_len ;
 payload32 = ( uint32_t * ) ioc -> encinput . buffer ;
 for ( i = 0 ;
 i < payload_len / 4 ;
 i ++ ) {
 payload32 [ i ] ^= ioc -> mask . u ;
 }
 for ( i *= 4 ;
 i < payload_len ;
 i ++ ) {
 ioc -> encinput . buffer [ i ] ^= ioc -> mask . c [ i % 4 ] ;
 }
 }
 trace_qio_channel_websock_payload_decode ( ioc , ioc -> opcode , ioc -> payload_remain ) ;
 if ( ioc -> opcode == QIO_CHANNEL_WEBSOCK_OPCODE_BINARY_FRAME ) {
 if ( payload_len ) {
 buffer_reserve ( & ioc -> rawinput , payload_len ) ;
 buffer_append ( & ioc -> rawinput , ioc -> encinput . buffer , payload_len ) ;
 }
 }
 else if ( ioc -> opcode == QIO_CHANNEL_WEBSOCK_OPCODE_CLOSE ) {
 error_setg ( errp , "websocket closed by peer" ) ;
 if ( payload_len ) {
 qio_channel_websock_encode_buffer ( ioc , & ioc -> encoutput , QIO_CHANNEL_WEBSOCK_OPCODE_CLOSE , & ioc -> encinput ) ;
 qio_channel_websock_write_wire ( ioc , NULL ) ;
 qio_channel_shutdown ( ioc -> master , QIO_CHANNEL_SHUTDOWN_BOTH , NULL ) ;
 }
 else {
 qio_channel_websock_write_close ( ioc , QIO_CHANNEL_WEBSOCK_STATUS_NORMAL , "peer requested close" ) ;
 }
 return - 1 ;
 }
 else if ( ioc -> opcode == QIO_CHANNEL_WEBSOCK_OPCODE_PING ) {
 buffer_reset ( & ioc -> ping_reply ) ;
 qio_channel_websock_encode_buffer ( ioc , & ioc -> ping_reply , QIO_CHANNEL_WEBSOCK_OPCODE_PONG , & ioc -> encinput ) ;
 }
 if ( payload_len ) {
 buffer_advance ( & ioc -> encinput , payload_len ) ;
 }
 return 0 ;
 }