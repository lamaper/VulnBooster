void ber_rewind ( BerElement * ber ) {
 ber -> ber_rwptr = NULL ;
 ber -> ber_sos_ptr = NULL ;
 ber -> ber_end = ber -> ber_ptr ;
 ber -> ber_ptr = ber -> ber_buf ;

 ber -> ber_usertag = 0 ;
