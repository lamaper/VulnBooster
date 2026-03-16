chunk_t x509_build_crlDistributionPoints ( linked_list_t * list , int extn ) {
 chunk_t crlDistributionPoints = chunk_empty ;
 enumerator_t * enumerator ;
 x509_cdp_t * cdp ;
 if ( list -> get_count ( list ) == 0 ) {
 return chunk_empty ;
 }
 enumerator = list -> create_enumerator ( list ) ;
 while ( enumerator -> enumerate ( enumerator , & cdp ) ) {
 chunk_t distributionPoint , crlIssuer = chunk_empty ;
 if ( cdp -> issuer ) {
 crlIssuer = asn1_wrap ( ASN1_CONTEXT_C_2 , "m" , build_generalName ( cdp -> issuer ) ) ;
 }
 distributionPoint = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_wrap ( ASN1_CONTEXT_C_0 , "m" , asn1_wrap ( ASN1_CONTEXT_C_0 , "m" , asn1_wrap ( ASN1_CONTEXT_S_6 , "c" , chunk_create ( cdp -> uri , strlen ( cdp -> uri ) ) ) ) ) , crlIssuer ) ;
 crlDistributionPoints = chunk_cat ( "mm" , crlDistributionPoints , distributionPoint ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 return asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( extn ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_SEQUENCE , "m" , crlDistributionPoints ) ) ) ;
 }