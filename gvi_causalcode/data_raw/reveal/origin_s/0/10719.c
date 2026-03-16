static Asn1Generic * DecodeAsn1DerUTCTime ( const unsigned char * buffer , uint32_t max_size , uint8_t depth , uint32_t * errcode ) {
 Asn1Generic * a ;
 a = DecodeAsn1DerIA5String ( buffer , max_size , depth , errcode ) ;
 if ( a != NULL ) a -> type = ASN1_UTCTIME ;
 return a ;
 }