static int DecodeAsn1BuildValue ( const unsigned char * * d_ptr , uint32_t * val , uint8_t numbytes , uint32_t * errcode ) {
 int i ;
 uint32_t value = 0 ;
 if ( numbytes > 4 ) {
 if ( errcode ) * errcode = ERR_DER_INVALID_SIZE ;
 value = 0xffffffff ;
 * val = value ;
 return - 1 ;
 }
 else {
 for ( i = 0 ;
 i < numbytes ;
 i ++ ) {
 value = value << 8 | ( * d_ptr ) [ 0 ] ;
 ( * d_ptr ) ++ ;
 }
 }
 * val = value ;
 return 0 ;
 }