ber_slen_t ber_write ( BerElement * ber , LDAP_CONST char * buf , ber_len_t len , int zero ) {
 char * * p ;
 assert ( ber != NULL ) ;
 assert ( buf != NULL ) ;
 assert ( LBER_VALID ( ber ) ) ;
 if ( zero != 0 ) {
 ber_log_printf ( LDAP_DEBUG_ANY , ber -> ber_debug , "%s" , "ber_write: nonzero 4th argument not supported\n" ) ;
 return ( - 1 ) ;
 }
 p = ber -> ber_sos_ptr == NULL ? & ber -> ber_ptr : & ber -> ber_sos_ptr ;
 if ( len > ( ber_len_t ) ( ber -> ber_end - * p ) ) {
 if ( ber_realloc ( ber , len ) != 0 ) return ( - 1 ) ;
 }
 AC_MEMCPY ( * p , buf , len ) ;
 * p += len ;
 return ( ( ber_slen_t ) len ) ;
 }