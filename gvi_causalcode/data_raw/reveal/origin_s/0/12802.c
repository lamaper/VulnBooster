int ber_len ( BerElement * ber ) {
 return ( ber -> ber_end - ber -> ber_buf ) ;
 }