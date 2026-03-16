int ber_flush ( Sockbuf * sb , BerElement * ber , int freeit ) {
 return ber_flush2 ( sb , ber , freeit ? LBER_FLUSH_FREE_ON_SUCCESS : LBER_FLUSH_FREE_NEVER ) ;
 }