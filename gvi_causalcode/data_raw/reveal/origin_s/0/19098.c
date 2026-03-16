static Asn1Generic * DecodeAsn1DerBoolean ( const unsigned char * buffer , uint32_t size , uint8_t depth , uint32_t * errcode ) {
 const unsigned char * d_ptr = buffer ;
 uint8_t numbytes ;
 uint32_t value ;
 Asn1Generic * a ;
 numbytes = d_ptr [ 1 ] ;
 d_ptr += 2 ;
 if ( DecodeAsn1BuildValue ( & d_ptr , & value , numbytes , errcode ) == - 1 ) {
 return NULL ;
 }
 a = Asn1GenericNew ( ) ;
 if ( a == NULL ) return NULL ;
 a -> type = ASN1_BOOLEAN ;
 a -> length = ( d_ptr - buffer ) ;
 a -> value = value ;
 return a ;
 }