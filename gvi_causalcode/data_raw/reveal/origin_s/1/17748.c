ber_tag_t ber_get_next ( Sockbuf * sb , ber_len_t * len , BerElement * ber ) {
 assert ( sb != NULL ) ;
 assert ( len != NULL ) ;
 assert ( ber != NULL ) ;
 assert ( SOCKBUF_VALID ( sb ) ) ;
 assert ( LBER_VALID ( ber ) ) ;
 if ( ber -> ber_debug & LDAP_DEBUG_TRACE ) {
 ber_log_printf ( LDAP_DEBUG_TRACE , ber -> ber_debug , "ber_get_next\n" ) ;
 }
 if ( ber -> ber_rwptr == NULL ) {
 assert ( ber -> ber_buf == NULL ) ;
 ber -> ber_rwptr = ( char * ) & ber -> ber_len - 1 ;
 ber -> ber_ptr = ber -> ber_rwptr ;
 ber -> ber_tag = 0 ;
 }
 while ( ber -> ber_rwptr > ( char * ) & ber -> ber_tag && ber -> ber_rwptr < ( char * ) & ber -> ber_len + LENSIZE * 2 ) {
 ber_slen_t sblen ;
 char buf [ sizeof ( ber -> ber_len ) - 1 ] ;
 ber_len_t tlen = 0 ;
 sock_errset ( 0 ) ;
 sblen = ( ( char * ) & ber -> ber_len + LENSIZE * 2 - 1 ) - ber -> ber_rwptr ;
 if ( sblen < 1 ) sblen = 1 ;
 sblen = ber_int_sb_read ( sb , ber -> ber_rwptr , sblen ) ;
 if ( sblen <= 0 ) return LBER_DEFAULT ;
 ber -> ber_rwptr += sblen ;
 if ( ber -> ber_ptr == ( char * ) & ber -> ber_len - 1 ) {
 ber_tag_t tag ;
 unsigned char * p = ( unsigned char * ) ber -> ber_ptr ;
 tag = * p ++ ;
 if ( ( tag & LBER_BIG_TAG_MASK ) == LBER_BIG_TAG_MASK ) {
 ber_len_t i ;
 for ( i = 1 ;
 ( char * ) p < ber -> ber_rwptr ;
 i ++ ) {
 tag <<= 8 ;
 tag |= * p ++ ;
 if ( ! ( tag & LBER_MORE_TAG_MASK ) ) break ;
 if ( i == sizeof ( ber_tag_t ) - 1 ) {
 sock_errset ( ERANGE ) ;
 return LBER_DEFAULT ;
 }
 }
 if ( ( char * ) p == ber -> ber_rwptr ) {
 sock_errset ( EWOULDBLOCK ) ;
 return LBER_DEFAULT ;
 }
 }
 ber -> ber_tag = tag ;
 ber -> ber_ptr = ( char * ) p ;
 }
 if ( ber -> ber_ptr == ber -> ber_rwptr ) {
 sock_errset ( EWOULDBLOCK ) ;
 return LBER_DEFAULT ;
 }
 if ( * ber -> ber_ptr & 0x80 ) {
 int i ;
 unsigned char * p = ( unsigned char * ) ber -> ber_ptr ;
 int llen = * p ++ & 0x7f ;
 if ( llen > LENSIZE ) {
 sock_errset ( ERANGE ) ;
 return LBER_DEFAULT ;
 }
 if ( ber -> ber_rwptr - ( char * ) p < llen ) {
 sock_errset ( EWOULDBLOCK ) ;
 return LBER_DEFAULT ;
 }
 for ( i = 0 ;
 i < llen ;
 i ++ ) {
 tlen <<= 8 ;
 tlen |= * p ++ ;
 }
 ber -> ber_ptr = ( char * ) p ;
 }
 else {
 tlen = * ( unsigned char * ) ber -> ber_ptr ++ ;
 }
 if ( ber -> ber_ptr < ( char * ) & ber -> ber_usertag ) {
 if ( ber -> ber_rwptr < ( char * ) & ber -> ber_usertag ) {
 sblen = ber -> ber_rwptr - ber -> ber_ptr ;
 }
 else {
 sblen = ( char * ) & ber -> ber_usertag - ber -> ber_ptr ;
 }
 AC_MEMCPY ( buf , ber -> ber_ptr , sblen ) ;
 ber -> ber_ptr += sblen ;
 }
 else {
 sblen = 0 ;
 }
 ber -> ber_len = tlen ;
 if ( ber -> ber_len == 0 ) {
 sock_errset ( ERANGE ) ;
 return LBER_DEFAULT ;
 }
 if ( sb -> sb_max_incoming && ber -> ber_len > sb -> sb_max_incoming ) {
 ber_log_printf ( LDAP_DEBUG_CONNS , ber -> ber_debug , "ber_get_next: sockbuf_max_incoming exceeded " "(%ld > %ld)\n" , ber -> ber_len , sb -> sb_max_incoming ) ;
 sock_errset ( ERANGE ) ;
 return LBER_DEFAULT ;
 }
 if ( ber -> ber_buf == NULL ) {
 ber_len_t l = ber -> ber_rwptr - ber -> ber_ptr ;
 if ( ber -> ber_len < sblen + l ) {
 sock_errset ( ERANGE ) ;
 return LBER_DEFAULT ;
 }
 ber -> ber_buf = ( char * ) ber_memalloc_x ( ber -> ber_len + 1 , ber -> ber_memctx ) ;
 if ( ber -> ber_buf == NULL ) {
 return LBER_DEFAULT ;
 }
 ber -> ber_end = ber -> ber_buf + ber -> ber_len ;
 if ( sblen ) {
 AC_MEMCPY ( ber -> ber_buf , buf , sblen ) ;
 }
 if ( l > 0 ) {
 AC_MEMCPY ( ber -> ber_buf + sblen , ber -> ber_ptr , l ) ;
 sblen += l ;
 }
 * ber -> ber_end = '\0' ;
 ber -> ber_ptr = ber -> ber_buf ;
 ber -> ber_usertag = 0 ;
 if ( ( ber_len_t ) sblen == ber -> ber_len ) {
 goto done ;
 }
 ber -> ber_rwptr = ber -> ber_buf + sblen ;
 }
 }
 if ( ( ber -> ber_rwptr >= ber -> ber_buf ) && ( ber -> ber_rwptr < ber -> ber_end ) ) {
 ber_slen_t res ;
 ber_slen_t to_go ;
 to_go = ber -> ber_end - ber -> ber_rwptr ;
 assert ( to_go > 0 ) ;
 sock_errset ( 0 ) ;
 res = ber_int_sb_read ( sb , ber -> ber_rwptr , to_go ) ;
 if ( res <= 0 ) return LBER_DEFAULT ;
 ber -> ber_rwptr += res ;
 if ( res < to_go ) {
 sock_errset ( EWOULDBLOCK ) ;
 return LBER_DEFAULT ;
 }
 done : ber -> ber_rwptr = NULL ;
 * len = ber -> ber_len ;
 if ( ber -> ber_debug ) {
 ber_log_printf ( LDAP_DEBUG_TRACE , ber -> ber_debug , "ber_get_next: tag 0x%lx len %ld contents:\n" , ber -> ber_tag , ber -> ber_len ) ;
 ber_log_dump ( LDAP_DEBUG_BER , ber -> ber_debug , ber , 1 ) ;
 }
 return ( ber -> ber_tag ) ;
 }
 assert ( 0 ) ;
 return LBER_DEFAULT ;
 }