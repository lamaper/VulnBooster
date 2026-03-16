void ber_reset ( BerElement * ber , int was_writing ) {
 assert ( ber != NULL ) ;
 assert ( LBER_VALID ( ber ) ) ;
 if ( was_writing ) {
 ber -> ber_end = ber -> ber_ptr ;
 ber -> ber_ptr = ber -> ber_buf ;
 }
 else {
 ber -> ber_ptr = ber -> ber_end ;
 }
 ber -> ber_rwptr = NULL ;
 }