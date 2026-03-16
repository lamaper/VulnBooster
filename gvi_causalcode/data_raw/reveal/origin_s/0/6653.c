static Asn1Generic * DecodeAsn1DerBitstring ( const unsigned char * buffer , uint32_t max_size , uint8_t depth , uint32_t * errcode ) {
 const unsigned char * d_ptr = buffer ;
 uint32_t length ;
 uint8_t numbytes , c ;
 Asn1Generic * a ;
 d_ptr ++ ;
 c = d_ptr [ 0 ] ;
 if ( ( c & ( 1 << 7 ) ) >> 7 == 0 ) {
 length = c ;
 d_ptr ++ ;
 }
 else {
 numbytes = c & 0x7f ;
 d_ptr ++ ;
 if ( DecodeAsn1BuildValue ( & d_ptr , & length , numbytes , errcode ) == - 1 ) {
 return NULL ;
 }
 }
 if ( length > max_size ) return NULL ;
 a = Asn1GenericNew ( ) ;
 if ( a == NULL ) return NULL ;
 a -> type = ASN1_BITSTRING ;
 a -> strlen = length ;
 a -> str = SCMalloc ( length ) ;
 if ( a -> str == NULL ) {
 SCFree ( a ) ;
 return NULL ;
 }
 memcpy ( a -> str , ( const char * ) d_ptr , length ) ;
 d_ptr += length ;
 a -> length = ( d_ptr - buffer ) ;
 return a ;
 }