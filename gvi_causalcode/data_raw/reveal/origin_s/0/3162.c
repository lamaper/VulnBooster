int ber_flush2 ( Sockbuf * sb , BerElement * ber , int freeit ) {
 ber_len_t towrite ;
 ber_slen_t rc ;
 assert ( sb != NULL ) ;
 assert ( ber != NULL ) ;
 assert ( SOCKBUF_VALID ( sb ) ) ;
 assert ( LBER_VALID ( ber ) ) ;
 if ( ber -> ber_rwptr == NULL ) {
 ber -> ber_rwptr = ber -> ber_buf ;
 }
 towrite = ber -> ber_ptr - ber -> ber_rwptr ;
 if ( sb -> sb_debug ) {
 ber_log_printf ( LDAP_DEBUG_TRACE , sb -> sb_debug , "ber_flush2: %ld bytes to sd %ld%s\n" , towrite , ( long ) sb -> sb_fd , ber -> ber_rwptr != ber -> ber_buf ? " (re-flush)" : "" ) ;
 ber_log_bprint ( LDAP_DEBUG_BER , sb -> sb_debug , ber -> ber_rwptr , towrite ) ;
 }
 while ( towrite > 0 ) {

 rc = ber_int_sb_write ( sb , ber -> ber_rwptr , 1 ) ;


 if ( freeit & LBER_FLUSH_FREE_ON_ERROR ) ber_free ( ber , 1 ) ;
 return - 1 ;
 }
 towrite -= rc ;
 ber -> ber_rwptr += rc ;
 }
 if ( freeit & LBER_FLUSH_FREE_ON_SUCCESS ) ber_free ( ber , 1 ) ;
 return 0 ;
 }