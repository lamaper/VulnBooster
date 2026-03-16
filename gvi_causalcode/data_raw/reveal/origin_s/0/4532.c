static void qio_channel_websock_encode_buffer ( QIOChannelWebsock * ioc , Buffer * output , uint8_t opcode , Buffer * buffer ) {
 size_t header_size ;
 union {
 char buf [ QIO_CHANNEL_WEBSOCK_HEADER_LEN_64_BIT ] ;
 QIOChannelWebsockHeader ws ;
 }
 header ;
 header . ws . b0 = QIO_CHANNEL_WEBSOCK_HEADER_FIELD_FIN | ( opcode & QIO_CHANNEL_WEBSOCK_HEADER_FIELD_OPCODE ) ;
 if ( buffer -> offset < QIO_CHANNEL_WEBSOCK_PAYLOAD_LEN_THRESHOLD_7_BIT ) {
 header . ws . b1 = ( uint8_t ) buffer -> offset ;
 header_size = QIO_CHANNEL_WEBSOCK_HEADER_LEN_7_BIT ;
 }
 else if ( buffer -> offset < QIO_CHANNEL_WEBSOCK_PAYLOAD_LEN_THRESHOLD_16_BIT ) {
 header . ws . b1 = QIO_CHANNEL_WEBSOCK_PAYLOAD_LEN_MAGIC_16_BIT ;
 header . ws . u . s16 . l16 = cpu_to_be16 ( ( uint16_t ) buffer -> offset ) ;
 header_size = QIO_CHANNEL_WEBSOCK_HEADER_LEN_16_BIT ;
 }
 else {
 header . ws . b1 = QIO_CHANNEL_WEBSOCK_PAYLOAD_LEN_MAGIC_64_BIT ;
 header . ws . u . s64 . l64 = cpu_to_be64 ( buffer -> offset ) ;
 header_size = QIO_CHANNEL_WEBSOCK_HEADER_LEN_64_BIT ;
 }
 header_size -= QIO_CHANNEL_WEBSOCK_HEADER_LEN_MASK ;
 trace_qio_channel_websock_encode ( ioc , opcode , header_size , buffer -> offset ) ;
 buffer_reserve ( output , header_size + buffer -> offset ) ;
 buffer_append ( output , header . buf , header_size ) ;
 buffer_append ( output , buffer -> buffer , buffer -> offset ) ;
 }