int dtls1_send_certificate_request ( SSL * s ) {
 unsigned char * p , * d ;
 int i , j , nl , off , n ;
 STACK_OF ( X509_NAME ) * sk = NULL ;
 X509_NAME * name ;
 BUF_MEM * buf ;
 unsigned int msg_len ;
 if ( s -> state == SSL3_ST_SW_CERT_REQ_A ) {
 buf = s -> init_buf ;
 d = p = ( unsigned char * ) & ( buf -> data [ DTLS1_HM_HEADER_LENGTH ] ) ;
 p ++ ;
 n = ssl3_get_req_cert_type ( s , p ) ;
 d [ 0 ] = n ;
 p += n ;
 n ++ ;
 off = n ;
 p += 2 ;
 n += 2 ;
 sk = SSL_get_client_CA_list ( s ) ;
 nl = 0 ;
 if ( sk != NULL ) {
 for ( i = 0 ;
 i < sk_X509_NAME_num ( sk ) ;
 i ++ ) {
 name = sk_X509_NAME_value ( sk , i ) ;
 j = i2d_X509_NAME ( name , NULL ) ;
 if ( ! BUF_MEM_grow_clean ( buf , DTLS1_HM_HEADER_LENGTH + n + j + 2 ) ) {
 SSLerr ( SSL_F_DTLS1_SEND_CERTIFICATE_REQUEST , ERR_R_BUF_LIB ) ;
 goto err ;
 }
 p = ( unsigned char * ) & ( buf -> data [ DTLS1_HM_HEADER_LENGTH + n ] ) ;
 if ( ! ( s -> options & SSL_OP_NETSCAPE_CA_DN_BUG ) ) {
 s2n ( j , p ) ;
 i2d_X509_NAME ( name , & p ) ;
 n += 2 + j ;
 nl += 2 + j ;
 }
 else {
 d = p ;
 i2d_X509_NAME ( name , & p ) ;
 j -= 2 ;
 s2n ( j , d ) ;
 j += 2 ;
 n += j ;
 nl += j ;
 }
 }
 }
 p = ( unsigned char * ) & ( buf -> data [ DTLS1_HM_HEADER_LENGTH + off ] ) ;
 s2n ( nl , p ) ;
 d = ( unsigned char * ) buf -> data ;
 * ( d ++ ) = SSL3_MT_CERTIFICATE_REQUEST ;
 l2n3 ( n , d ) ;
 s2n ( s -> d1 -> handshake_write_seq , d ) ;
 s -> d1 -> handshake_write_seq ++ ;
 s -> init_num = n + DTLS1_HM_HEADER_LENGTH ;
 s -> init_off = 0 ;

 * ( p ++ ) = SSL3_MT_SERVER_DONE ;
 * ( p ++ ) = 0 ;
 * ( p ++ ) = 0 ;
 * ( p ++ ) = 0 ;
 s -> init_num += 4 ;

 dtls1_set_message_header ( s , ( void * ) s -> init_buf -> data , SSL3_MT_CERTIFICATE_REQUEST , msg_len , 0 , msg_len ) ;
 dtls1_buffer_message ( s , 0 ) ;
 s -> state = SSL3_ST_SW_CERT_REQ_B ;
 }
 return ( dtls1_do_write ( s , SSL3_RT_HANDSHAKE ) ) ;
 err : return ( - 1 ) ;
 }