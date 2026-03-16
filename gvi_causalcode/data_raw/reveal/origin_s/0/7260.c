static Asn1Generic * DecodeAsn1DerSet ( const unsigned char * buffer , uint32_t max_size , uint8_t depth , uint32_t * errcode ) {
 const unsigned char * d_ptr = buffer ;
 uint32_t d_length , numbytes , el_max_size ;
 uint8_t c ;
 uint32_t seq_index ;
 Asn1Generic * node ;
 Asn1Generic * child ;
 d_ptr ++ ;
 node = Asn1GenericNew ( ) ;
 if ( node == NULL ) return NULL ;
 node -> type = ASN1_SET ;
 node -> data = NULL ;
 c = d_ptr [ 0 ] ;
 if ( ( c & ( 1 << 7 ) ) >> 7 == 0 ) {
 d_length = c ;
 d_ptr ++ ;
 }
 else {
 numbytes = c & 0x7f ;
 d_ptr ++ ;
 if ( DecodeAsn1BuildValue ( & d_ptr , & d_length , numbytes , errcode ) == - 1 ) {
 SCFree ( node ) ;
 return NULL ;
 }
 }
 node -> length = d_length + ( d_ptr - buffer ) ;
 if ( node -> length > max_size || node -> length < d_length ) {
 if ( errcode ) * errcode = ERR_DER_ELEMENT_SIZE_TOO_BIG ;
 SCFree ( node ) ;
 return NULL ;
 }
 seq_index = 0 ;
 el_max_size = max_size - ( d_ptr - buffer ) ;
 child = DecodeAsn1DerGeneric ( d_ptr , el_max_size , depth , seq_index , errcode ) ;
 if ( child == NULL ) {
 DerFree ( node ) ;
 return NULL ;
 }
 node -> data = child ;
 return ( Asn1Generic * ) node ;
 }