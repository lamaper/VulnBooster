static Asn1Generic * DecodeAsn1DerInteger ( const unsigned char * buffer , uint32_t size , uint8_t depth , uint32_t * errcode ) {
 const unsigned char * d_ptr = buffer ;
 uint8_t numbytes ;
 uint32_t value ;
 uint32_t i ;
 Asn1Generic * a ;
 numbytes = d_ptr [ 1 ] ;
 if ( numbytes > size ) {
 if ( errcode ) * errcode = ERR_DER_ELEMENT_SIZE_TOO_BIG ;
 return NULL ;
 }
 d_ptr += 2 ;
 value = 0 ;
 if ( numbytes > 4 ) {
 value = 0xffffffff ;
 }
 else {
 for ( i = 0 ;
 i < numbytes ;
 i ++ ) {
 value = value << 8 | d_ptr [ i ] ;
 }
 }
 a = Asn1GenericNew ( ) ;
 if ( a == NULL ) return NULL ;
 a -> type = ASN1_INTEGER ;
 a -> length = ( d_ptr - buffer ) + numbytes ;
 a -> value = value ;
 a -> str = SCMalloc ( 2 * numbytes + 1 ) ;
 if ( a -> str == NULL ) {
 SCFree ( a ) ;
 return NULL ;
 }
 for ( i = 0 ;
 i < numbytes ;
 i ++ ) {
 snprintf ( a -> str + 2 * i , 2 * ( numbytes - i ) + 1 , "%02X" , d_ptr [ i ] ) ;
 }
 a -> str [ 2 * numbytes ] = '\0' ;
 return a ;
 }