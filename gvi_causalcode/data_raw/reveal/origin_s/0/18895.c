static Asn1Generic * DecodeAsn1DerUTF8String ( const unsigned char * buffer , uint32_t max_size , uint8_t depth , uint32_t * errcode ) {
 Asn1Generic * a = DecodeAsn1DerOctetString ( buffer , max_size , depth , errcode ) ;
 if ( a != NULL ) a -> type = ASN1_UTF8STRING ;
 return a ;
 }