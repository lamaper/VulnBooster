static void qio_channel_websock_handshake_send_res_err ( QIOChannelWebsock * ioc , const char * resdata ) {
 char * date = qio_channel_websock_date_str ( ) ;
 qio_channel_websock_handshake_send_res ( ioc , resdata , date ) ;
 g_free ( date ) ;
 }