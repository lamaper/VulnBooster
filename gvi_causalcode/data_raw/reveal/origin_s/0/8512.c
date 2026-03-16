static int qio_channel_websock_decode_header ( QIOChannelWebsock * ioc , Error * * errp ) {
 unsigned char opcode , fin , has_mask ;
 size_t header_size ;
 size_t payload_len ;
 QIOChannelWebsockHeader * header = ( QIOChannelWebsockHeader * ) ioc -> encinput . buffer ;
 if ( ioc -> payload_remain ) {
 error_setg ( errp , "Decoding header but %zu bytes of payload remain" , ioc -> payload_remain ) ;
 qio_channel_websock_write_close ( ioc , QIO_CHANNEL_WEBSOCK_STATUS_SERVER_ERR , "internal server error" ) ;
 return - 1 ;
 }
 if ( ioc -> encinput . offset < QIO_CHANNEL_WEBSOCK_HEADER_LEN_7_BIT ) {
 return QIO_CHANNEL_ERR_BLOCK ;
 }
 fin = header -> b0 & QIO_CHANNEL_WEBSOCK_HEADER_FIELD_FIN ;
 opcode = header -> b0 & QIO_CHANNEL_WEBSOCK_HEADER_FIELD_OPCODE ;
 has_mask = header -> b1 & QIO_CHANNEL_WEBSOCK_HEADER_FIELD_HAS_MASK ;
 payload_len = header -> b1 & QIO_CHANNEL_WEBSOCK_HEADER_FIELD_PAYLOAD_LEN ;
 if ( opcode ) {
 ioc -> opcode = opcode ;
 }
 else {
 opcode = ioc -> opcode ;
 }
 trace_qio_channel_websock_header_partial_decode ( ioc , payload_len , fin , opcode , ( int ) has_mask ) ;
 if ( opcode == QIO_CHANNEL_WEBSOCK_OPCODE_CLOSE ) {
 return 0 ;
 }
 if ( ! fin ) {
 if ( opcode != QIO_CHANNEL_WEBSOCK_OPCODE_BINARY_FRAME ) {
 error_setg ( errp , "only binary websocket frames may be fragmented" ) ;
 qio_channel_websock_write_close ( ioc , QIO_CHANNEL_WEBSOCK_STATUS_POLICY , "only binary frames may be fragmented" ) ;
 return - 1 ;
 }
 }
 else {
 if ( opcode != QIO_CHANNEL_WEBSOCK_OPCODE_BINARY_FRAME && opcode != QIO_CHANNEL_WEBSOCK_OPCODE_CLOSE && opcode != QIO_CHANNEL_WEBSOCK_OPCODE_PING && opcode != QIO_CHANNEL_WEBSOCK_OPCODE_PONG ) {
 error_setg ( errp , "unsupported opcode: %#04x;
 only binary, close, " "ping, and pong websocket frames are supported" , opcode ) ;
 qio_channel_websock_write_close ( ioc , QIO_CHANNEL_WEBSOCK_STATUS_INVALID_DATA , "only binary, close, ping, and pong frames are supported" ) ;
 return - 1 ;
 }
 }
 if ( ! has_mask ) {
 error_setg ( errp , "client websocket frames must be masked" ) ;
 qio_channel_websock_write_close ( ioc , QIO_CHANNEL_WEBSOCK_STATUS_PROTOCOL_ERR , "client frames must be masked" ) ;
 return - 1 ;
 }
 if ( payload_len < QIO_CHANNEL_WEBSOCK_PAYLOAD_LEN_MAGIC_16_BIT ) {
 ioc -> payload_remain = payload_len ;
 header_size = QIO_CHANNEL_WEBSOCK_HEADER_LEN_7_BIT ;
 ioc -> mask = header -> u . m ;
 }
 else if ( opcode & QIO_CHANNEL_WEBSOCK_CONTROL_OPCODE_MASK ) {
 error_setg ( errp , "websocket control frame is too large" ) ;
 qio_channel_websock_write_close ( ioc , QIO_CHANNEL_WEBSOCK_STATUS_PROTOCOL_ERR , "control frame is too large" ) ;
 return - 1 ;
 }
 else if ( payload_len == QIO_CHANNEL_WEBSOCK_PAYLOAD_LEN_MAGIC_16_BIT && ioc -> encinput . offset >= QIO_CHANNEL_WEBSOCK_HEADER_LEN_16_BIT ) {
 ioc -> payload_remain = be16_to_cpu ( header -> u . s16 . l16 ) ;
 header_size = QIO_CHANNEL_WEBSOCK_HEADER_LEN_16_BIT ;
 ioc -> mask = header -> u . s16 . m16 ;
 }
 else if ( payload_len == QIO_CHANNEL_WEBSOCK_PAYLOAD_LEN_MAGIC_64_BIT && ioc -> encinput . offset >= QIO_CHANNEL_WEBSOCK_HEADER_LEN_64_BIT ) {
 ioc -> payload_remain = be64_to_cpu ( header -> u . s64 . l64 ) ;
 header_size = QIO_CHANNEL_WEBSOCK_HEADER_LEN_64_BIT ;
 ioc -> mask = header -> u . s64 . m64 ;
 }
 else {
 return QIO_CHANNEL_ERR_BLOCK ;
 }
 trace_qio_channel_websock_header_full_decode ( ioc , header_size , ioc -> payload_remain , ioc -> mask . u ) ;
 buffer_advance ( & ioc -> encinput , header_size ) ;
 return 0 ;
 }