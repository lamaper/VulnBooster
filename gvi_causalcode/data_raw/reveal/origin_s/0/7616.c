void ber_free_buf ( BerElement * ber ) {
 assert ( LBER_VALID ( ber ) ) ;
 if ( ber -> ber_buf ) ber_memfree_x ( ber -> ber_buf , ber -> ber_memctx ) ;
 ber -> ber_buf = NULL ;
 ber -> ber_sos_ptr = NULL ;
 ber -> ber_valid = LBER_UNINITIALIZED ;
 }