int ber_ptrlen ( BerElement * ber ) {
 return ( ber -> ber_ptr - ber -> ber_buf ) ;
 }