Asn1Generic * DecodeDer ( const unsigned char * buffer , uint32_t size , uint32_t * errcode ) {
 const unsigned char * d_ptr = buffer ;
 uint32_t d_length , numbytes ;
 Asn1Generic * cert ;
 uint8_t c ;
 if ( d_ptr [ 0 ] != 0x30 && d_ptr [ 1 ] != 0x82 ) return NULL ;
 c = d_ptr [ 1 ] ;
 if ( ( c & ( 1 << 7 ) ) >> 7 != 1 ) return NULL ;
 numbytes = c & 0x7f ;
 d_ptr += 2 ;
 if ( DecodeAsn1BuildValue ( & d_ptr , & d_length , numbytes , errcode ) == - 1 ) {
 return NULL ;
 }
 if ( d_length + ( d_ptr - buffer ) != size ) return NULL ;
 if ( errcode ) * errcode = 0 ;
 cert = DecodeAsn1DerGeneric ( buffer , size , 0 , 0 , errcode ) ;
 return cert ;
 }