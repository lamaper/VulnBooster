static void parse_keyUsage ( chunk_t blob , private_x509_cert_t * this ) {
 enum {
 KU_DIGITAL_SIGNATURE = 0 , KU_NON_REPUDIATION = 1 , KU_KEY_ENCIPHERMENT = 2 , KU_DATA_ENCIPHERMENT = 3 , KU_KEY_AGREEMENT = 4 , KU_KEY_CERT_SIGN = 5 , KU_CRL_SIGN = 6 , KU_ENCIPHER_ONLY = 7 , KU_DECIPHER_ONLY = 8 , }
 ;
 if ( asn1_unwrap ( & blob , & blob ) == ASN1_BIT_STRING && blob . len ) {
 int bit , byte , unused = blob . ptr [ 0 ] ;
 blob = chunk_skip ( blob , 1 ) ;
 for ( byte = 0 ;
 byte < blob . len ;
 byte ++ ) {
 for ( bit = 0 ;
 bit < 8 ;
 bit ++ ) {
 if ( byte == blob . len - 1 && bit > ( 7 - unused ) ) {
 break ;
 }
 if ( blob . ptr [ byte ] & 1 << ( 7 - bit ) ) {
 switch ( byte * 8 + bit ) {
 case KU_CRL_SIGN : this -> flags |= X509_CRL_SIGN ;
 break ;
 case KU_KEY_CERT_SIGN : case KU_DIGITAL_SIGNATURE : case KU_NON_REPUDIATION : case KU_KEY_ENCIPHERMENT : case KU_DATA_ENCIPHERMENT : case KU_KEY_AGREEMENT : case KU_ENCIPHER_ONLY : case KU_DECIPHER_ONLY : break ;
 }
 }
 }
 }
 }
 }