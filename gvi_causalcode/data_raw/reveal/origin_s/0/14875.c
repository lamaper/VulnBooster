static Asn1Generic * DecodeAsn1DerOid ( const unsigned char * buffer , uint32_t max_size , uint8_t depth , uint32_t * errcode ) {
 const unsigned char * d_ptr = buffer ;
 uint32_t oid_length , oid_value ;
 uint8_t numbytes , c ;
 Asn1Generic * a ;
 uint32_t i ;
 d_ptr ++ ;
 c = d_ptr [ 0 ] ;
 if ( ( c & ( 1 << 7 ) ) >> 7 == 0 ) {
 oid_length = c ;
 d_ptr ++ ;
 }
 else {
 numbytes = c & 0x7f ;
 d_ptr ++ ;
 if ( DecodeAsn1BuildValue ( & d_ptr , & oid_length , numbytes , errcode ) == - 1 ) {
 return NULL ;
 }
 }
 if ( oid_length > max_size ) return NULL ;
 a = Asn1GenericNew ( ) ;
 if ( a == NULL ) return NULL ;
 a -> type = ASN1_OID ;
 a -> str = SCMalloc ( MAX_OID_LENGTH ) ;
 if ( a -> str == NULL ) {
 SCFree ( a ) ;
 return NULL ;
 }
 snprintf ( a -> str , MAX_OID_LENGTH , "%d.%d" , ( d_ptr [ 0 ] / 40 ) , ( d_ptr [ 0 ] % 40 ) ) ;
 d_ptr ++ ;
 for ( i = 1 ;
 i < oid_length ;
 ) {
 int s = strlen ( a -> str ) ;
 c = d_ptr [ 0 ] ;
 oid_value = 0 ;
 while ( i < oid_length && ( c & ( 1 << 7 ) ) == 1 << 7 ) {
 oid_value = oid_value << 7 | ( c & ~ ( 1 << 7 ) ) ;
 d_ptr ++ ;
 c = d_ptr [ 0 ] ;
 i ++ ;
 }
 oid_value = oid_value << 7 | c ;
 d_ptr ++ ;
 i ++ ;
 snprintf ( a -> str + s , MAX_OID_LENGTH - s , ".%d" , oid_value ) ;
 }
 a -> length = ( d_ptr - buffer ) ;
 return a ;
 }