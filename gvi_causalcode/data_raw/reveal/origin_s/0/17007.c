static bool parse_extendedKeyUsage ( chunk_t blob , int level0 , private_x509_cert_t * this ) {
 asn1_parser_t * parser ;
 chunk_t object ;
 int objectID ;
 bool success ;
 parser = asn1_parser_create ( extendedKeyUsageObjects , blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 if ( objectID == EXT_KEY_USAGE_PURPOSE_ID ) {
 switch ( asn1_known_oid ( object ) ) {
 case OID_SERVER_AUTH : this -> flags |= X509_SERVER_AUTH ;
 break ;
 case OID_CLIENT_AUTH : this -> flags |= X509_CLIENT_AUTH ;
 break ;
 case OID_IKE_INTERMEDIATE : this -> flags |= X509_IKE_INTERMEDIATE ;
 break ;
 case OID_OCSP_SIGNING : this -> flags |= X509_OCSP_SIGNER ;
 break ;
 case OID_MS_SMARTCARD_LOGON : this -> flags |= X509_MS_SMARTCARD_LOGON ;
 break ;
 default : break ;
 }
 }
 }
 success = parser -> success ( parser ) ;
 parser -> destroy ( parser ) ;
 return success ;
 }