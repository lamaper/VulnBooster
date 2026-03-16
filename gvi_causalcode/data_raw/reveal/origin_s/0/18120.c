int dtls1_send_server_done ( SSL * s ) {
 unsigned char * p ;
 if ( s -> state == SSL3_ST_SW_SRVR_DONE_A ) {
 p = ( unsigned char * ) s -> init_buf -> data ;
 p = dtls1_set_message_header ( s , p , SSL3_MT_SERVER_DONE , 0 , 0 , 0 ) ;
 s -> state = SSL3_ST_SW_SRVR_DONE_B ;
 s -> init_num = DTLS1_HM_HEADER_LENGTH ;
 s -> init_off = 0 ;
 dtls1_buffer_message ( s , 0 ) ;
 }
 return ( dtls1_do_write ( s , SSL3_RT_HANDSHAKE ) ) ;
 }