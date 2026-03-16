int dtls1_send_hello_request ( SSL * s ) {
 unsigned char * p ;
 if ( s -> state == SSL3_ST_SW_HELLO_REQ_A ) {
 p = ( unsigned char * ) s -> init_buf -> data ;
 p = dtls1_set_message_header ( s , p , SSL3_MT_HELLO_REQUEST , 0 , 0 , 0 ) ;
 s -> state = SSL3_ST_SW_HELLO_REQ_B ;
 s -> init_num = DTLS1_HM_HEADER_LENGTH ;
 s -> init_off = 0 ;
 }
 return ( dtls1_do_write ( s , SSL3_RT_HANDSHAKE ) ) ;
 }