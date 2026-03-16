int dtls1_send_server_hello ( SSL * s ) {
 unsigned char * buf ;
 unsigned char * p , * d ;
 int i ;
 unsigned int sl ;
 unsigned long l ;
 if ( s -> state == SSL3_ST_SW_SRVR_HELLO_A ) {
 buf = ( unsigned char * ) s -> init_buf -> data ;
 p = s -> s3 -> server_random ;
 ssl_fill_hello_random ( s , 1 , p , SSL3_RANDOM_SIZE ) ;
 d = p = & ( buf [ DTLS1_HM_HEADER_LENGTH ] ) ;
 * ( p ++ ) = s -> version >> 8 ;
 * ( p ++ ) = s -> version & 0xff ;
 memcpy ( p , s -> s3 -> server_random , SSL3_RANDOM_SIZE ) ;
 p += SSL3_RANDOM_SIZE ;
 if ( ! ( s -> ctx -> session_cache_mode & SSL_SESS_CACHE_SERVER ) ) s -> session -> session_id_length = 0 ;
 sl = s -> session -> session_id_length ;
 if ( sl > sizeof s -> session -> session_id ) {
 SSLerr ( SSL_F_DTLS1_SEND_SERVER_HELLO , ERR_R_INTERNAL_ERROR ) ;
 return - 1 ;
 }
 * ( p ++ ) = sl ;
 memcpy ( p , s -> session -> session_id , sl ) ;
 p += sl ;
 if ( s -> s3 -> tmp . new_cipher == NULL ) return - 1 ;
 i = ssl3_put_cipher_by_char ( s -> s3 -> tmp . new_cipher , p ) ;
 p += i ;


 else * ( p ++ ) = s -> s3 -> tmp . new_compression -> id ;

 SSLerr ( SSL_F_DTLS1_SEND_SERVER_HELLO , SSL_R_SERVERHELLO_TLSEXT ) ;
 return - 1 ;
 }
 if ( ( p = ssl_add_serverhello_tlsext ( s , p , buf + SSL3_RT_MAX_PLAIN_LENGTH ) ) == NULL ) {
 SSLerr ( SSL_F_DTLS1_SEND_SERVER_HELLO , ERR_R_INTERNAL_ERROR ) ;
 return - 1 ;
 }

 d = buf ;
 d = dtls1_set_message_header ( s , d , SSL3_MT_SERVER_HELLO , l , 0 , l ) ;
 s -> state = SSL3_ST_SW_SRVR_HELLO_B ;
 s -> init_num = p - buf ;
 s -> init_off = 0 ;
 dtls1_buffer_message ( s , 0 ) ;
 }
 return ( dtls1_do_write ( s , SSL3_RT_HANDSHAKE ) ) ;
 }