int dtls1_send_newsession_ticket ( SSL * s ) {
 if ( s -> state == SSL3_ST_SW_SESSION_TICKET_A ) {
 unsigned char * p , * senc , * macstart ;
 int len , slen ;
 unsigned int hlen , msg_len ;
 EVP_CIPHER_CTX ctx ;
 HMAC_CTX hctx ;
 SSL_CTX * tctx = s -> initial_ctx ;
 unsigned char iv [ EVP_MAX_IV_LENGTH ] ;
 unsigned char key_name [ 16 ] ;
 slen = i2d_SSL_SESSION ( s -> session , NULL ) ;
 if ( slen > 0xFF00 ) return - 1 ;
 if ( ! BUF_MEM_grow ( s -> init_buf , DTLS1_HM_HEADER_LENGTH + 22 + EVP_MAX_IV_LENGTH + EVP_MAX_BLOCK_LENGTH + EVP_MAX_MD_SIZE + slen ) ) return - 1 ;
 senc = OPENSSL_malloc ( slen ) ;
 if ( ! senc ) return - 1 ;
 p = senc ;
 i2d_SSL_SESSION ( s -> session , & p ) ;
 p = ( unsigned char * ) & ( s -> init_buf -> data [ DTLS1_HM_HEADER_LENGTH ] ) ;
 EVP_CIPHER_CTX_init ( & ctx ) ;
 HMAC_CTX_init ( & hctx ) ;
 if ( tctx -> tlsext_ticket_key_cb ) {
 if ( tctx -> tlsext_ticket_key_cb ( s , key_name , iv , & ctx , & hctx , 1 ) < 0 ) {
 OPENSSL_free ( senc ) ;
 return - 1 ;
 }
 }
 else {
 RAND_pseudo_bytes ( iv , 16 ) ;
 EVP_EncryptInit_ex ( & ctx , EVP_aes_128_cbc ( ) , NULL , tctx -> tlsext_tick_aes_key , iv ) ;
 HMAC_Init_ex ( & hctx , tctx -> tlsext_tick_hmac_key , 16 , tlsext_tick_md ( ) , NULL ) ;
 memcpy ( key_name , tctx -> tlsext_tick_key_name , 16 ) ;
 }
 l2n ( s -> session -> tlsext_tick_lifetime_hint , p ) ;
 p += 2 ;
 macstart = p ;
 memcpy ( p , key_name , 16 ) ;
 p += 16 ;
 memcpy ( p , iv , EVP_CIPHER_CTX_iv_length ( & ctx ) ) ;
 p += EVP_CIPHER_CTX_iv_length ( & ctx ) ;
 EVP_EncryptUpdate ( & ctx , p , & len , senc , slen ) ;
 p += len ;
 EVP_EncryptFinal ( & ctx , p , & len ) ;
 p += len ;
 EVP_CIPHER_CTX_cleanup ( & ctx ) ;
 HMAC_Update ( & hctx , macstart , p - macstart ) ;
 HMAC_Final ( & hctx , p , & hlen ) ;
 HMAC_CTX_cleanup ( & hctx ) ;
 p += hlen ;
 len = p - ( unsigned char * ) ( s -> init_buf -> data ) ;
 p = ( unsigned char * ) & ( s -> init_buf -> data [ DTLS1_HM_HEADER_LENGTH ] ) + 4 ;
 s2n ( len - DTLS1_HM_HEADER_LENGTH - 6 , p ) ;
 s -> init_num = len ;
 s -> state = SSL3_ST_SW_SESSION_TICKET_B ;
 s -> init_off = 0 ;
 OPENSSL_free ( senc ) ;
 msg_len = s -> init_num - DTLS1_HM_HEADER_LENGTH ;
 dtls1_set_message_header ( s , ( void * ) s -> init_buf -> data , SSL3_MT_NEWSESSION_TICKET , msg_len , 0 , msg_len ) ;
 dtls1_buffer_message ( s , 0 ) ;
 }
 return ( dtls1_do_write ( s , SSL3_RT_HANDSHAKE ) ) ;
 }