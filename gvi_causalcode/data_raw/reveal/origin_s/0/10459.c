static bool parse_certificatePolicies ( chunk_t blob , int level0 , private_x509_cert_t * this ) {
 x509_cert_policy_t * policy = NULL ;
 asn1_parser_t * parser ;
 chunk_t object ;
 int objectID , qualifier = OID_UNKNOWN ;
 bool success ;
 parser = asn1_parser_create ( certificatePoliciesObject , blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 switch ( objectID ) {
 case CERT_POLICY_ID : INIT ( policy , . oid = chunk_clone ( object ) , ) ;
 this -> cert_policies -> insert_last ( this -> cert_policies , policy ) ;
 break ;
 case CERT_POLICY_QUALIFIER_ID : qualifier = asn1_known_oid ( object ) ;
 break ;
 case CERT_POLICY_CPS_URI : if ( policy && ! policy -> cps_uri && object . len && qualifier == OID_POLICY_QUALIFIER_CPS && chunk_printable ( object , NULL , 0 ) ) {
 policy -> cps_uri = strndup ( object . ptr , object . len ) ;
 }
 break ;
 case CERT_POLICY_EXPLICIT_TEXT : break ;
 default : break ;
 }
 }
 success = parser -> success ( parser ) ;
 parser -> destroy ( parser ) ;
 return success ;
 }