static Asn1Generic * DecodeAsn1DerGeneric ( const unsigned char * buffer , uint32_t max_size , uint8_t depth , int seq_index , uint32_t * errcode ) {
 const unsigned char * d_ptr = buffer ;
 uint32_t numbytes , el_max_size ;
 Asn1ElementType el ;
 uint8_t c ;
 uint32_t i ;
 Asn1Generic * child ;
 uint8_t el_type ;
 el . cls = ( d_ptr [ 0 ] & 0xc0 ) >> 6 ;
 el . pc = ( d_ptr [ 0 ] & 0x20 ) >> 5 ;
 el . tag = ( d_ptr [ 0 ] & 0x1f ) ;
 el_type = el . tag ;
 if ( el . tag == 0x1f ) return NULL ;
 switch ( el . cls ) {
 case ASN1_CLASS_CONTEXTSPEC : if ( depth == 2 && el . tag == 0 ) {
 el_type = ASN1_SEQUENCE ;
 break ;
 }
 if ( depth == 2 && el . tag == 1 ) {
 el_type = ASN1_BITSTRING ;
 break ;
 }
 if ( depth == 2 && el . tag == 2 ) {
 el_type = ASN1_BITSTRING ;
 break ;
 }
 if ( depth == 2 && el . tag == 3 ) {
 el_type = ASN1_SEQUENCE ;
 break ;
 }
 break ;
 }
 ;
 el_max_size = max_size - ( d_ptr - buffer ) ;
 switch ( el_type ) {
 case ASN1_INTEGER : child = DecodeAsn1DerInteger ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 case ASN1_BOOLEAN : child = DecodeAsn1DerBoolean ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 case ASN1_NULL : child = DecodeAsn1DerNull ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 case ASN1_BITSTRING : child = DecodeAsn1DerBitstring ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 case ASN1_OID : child = DecodeAsn1DerOid ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 case ASN1_IA5STRING : child = DecodeAsn1DerIA5String ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 case ASN1_OCTETSTRING : child = DecodeAsn1DerOctetString ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 case ASN1_UTF8STRING : child = DecodeAsn1DerUTF8String ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 case ASN1_PRINTSTRING : child = DecodeAsn1DerPrintableString ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 case ASN1_SEQUENCE : child = DecodeAsn1DerSequence ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 case ASN1_SET : child = DecodeAsn1DerSet ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 case ASN1_T61STRING : child = DecodeAsn1DerT61String ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 case ASN1_UTCTIME : child = DecodeAsn1DerUTCTime ( d_ptr , el_max_size , depth + 1 , errcode ) ;
 break ;
 default : child = NULL ;
 child = Asn1GenericNew ( ) ;
 if ( child == NULL ) break ;
 child -> type = el . tag ;
 const unsigned char * save_d_ptr = d_ptr ;
 d_ptr ++ ;
 c = d_ptr [ 0 ] ;
 if ( ( c & ( 1 << 7 ) ) >> 7 == 0 ) {
 child -> length = c ;
 d_ptr ++ ;
 }
 else {
 numbytes = c & 0x7f ;
 if ( numbytes > el_max_size ) {
 SCFree ( child ) ;
 if ( errcode ) * errcode = ERR_DER_ELEMENT_SIZE_TOO_BIG ;
 return NULL ;
 }
 child -> length = 0 ;
 d_ptr ++ ;
 for ( i = 0 ;
 i < numbytes ;
 i ++ ) {
 child -> length = child -> length << 8 | d_ptr [ 0 ] ;
 d_ptr ++ ;
 }
 }
 child -> length += ( d_ptr - save_d_ptr ) ;
 break ;
 }
 ;
 if ( child == NULL ) return NULL ;
 child -> header = el ;
 return child ;
 }