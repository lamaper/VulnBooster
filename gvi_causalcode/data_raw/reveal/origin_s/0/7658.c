static bool parse_certificate ( private_x509_cert_t * this ) {
 asn1_parser_t * parser ;
 chunk_t object ;
 int objectID ;
 int extn_oid = OID_UNKNOWN ;
 int sig_alg = OID_UNKNOWN ;
 bool success = FALSE ;
 bool critical = FALSE ;
 parser = asn1_parser_create ( certObjects , this -> encoding ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 u_int level = parser -> get_level ( parser ) + 1 ;
 switch ( objectID ) {
 case X509_OBJ_TBS_CERTIFICATE : this -> tbsCertificate = object ;
 break ;
 case X509_OBJ_VERSION : this -> version = ( object . len ) ? ( 1 + ( u_int ) * object . ptr ) : 1 ;
 if ( this -> version < 1 || this -> version > 3 ) {
 DBG1 ( DBG_ASN , "X.509v%d not supported" , this -> version ) ;
 goto end ;
 }
 else {
 DBG2 ( DBG_ASN , " X.509v%d" , this -> version ) ;
 }
 break ;
 case X509_OBJ_SERIAL_NUMBER : this -> serialNumber = object ;
 break ;
 case X509_OBJ_SIG_ALG : sig_alg = asn1_parse_algorithmIdentifier ( object , level , NULL ) ;
 break ;
 case X509_OBJ_ISSUER : this -> issuer = identification_create_from_encoding ( ID_DER_ASN1_DN , object ) ;
 DBG2 ( DBG_ASN , " '%Y'" , this -> issuer ) ;
 break ;
 case X509_OBJ_NOT_BEFORE : this -> notBefore = asn1_parse_time ( object , level ) ;
 break ;
 case X509_OBJ_NOT_AFTER : this -> notAfter = asn1_parse_time ( object , level ) ;
 break ;
 case X509_OBJ_SUBJECT : this -> subject = identification_create_from_encoding ( ID_DER_ASN1_DN , object ) ;
 DBG2 ( DBG_ASN , " '%Y'" , this -> subject ) ;
 break ;
 case X509_OBJ_SUBJECT_PUBLIC_KEY_INFO : DBG2 ( DBG_ASN , "-- > --" ) ;
 this -> public_key = lib -> creds -> create ( lib -> creds , CRED_PUBLIC_KEY , KEY_ANY , BUILD_BLOB_ASN1_DER , object , BUILD_END ) ;
 DBG2 ( DBG_ASN , "-- < --" ) ;
 if ( this -> public_key == NULL ) {
 goto end ;
 }
 break ;
 case X509_OBJ_OPTIONAL_EXTENSIONS : if ( this -> version != 3 ) {
 DBG1 ( DBG_ASN , "Only X.509v3 certificates have extensions" ) ;
 goto end ;
 }
 break ;
 case X509_OBJ_EXTN_ID : extn_oid = asn1_known_oid ( object ) ;
 break ;
 case X509_OBJ_CRITICAL : critical = object . len && * object . ptr ;
 DBG2 ( DBG_ASN , " %s" , critical ? "TRUE" : "FALSE" ) ;
 break ;
 case X509_OBJ_EXTN_VALUE : {
 switch ( extn_oid ) {
 case OID_SUBJECT_KEY_ID : if ( ! asn1_parse_simple_object ( & object , ASN1_OCTET_STRING , level , "keyIdentifier" ) ) {
 goto end ;
 }
 this -> subjectKeyIdentifier = object ;
 break ;
 case OID_SUBJECT_ALT_NAME : if ( ! x509_parse_generalNames ( object , level , FALSE , this -> subjectAltNames ) ) {
 goto end ;
 }
 break ;
 case OID_BASIC_CONSTRAINTS : if ( ! parse_basicConstraints ( object , level , this ) ) {
 goto end ;
 }
 break ;
 case OID_CRL_DISTRIBUTION_POINTS : if ( ! x509_parse_crlDistributionPoints ( object , level , this -> crl_uris ) ) {
 goto end ;
 }
 break ;
 case OID_AUTHORITY_KEY_ID : chunk_free ( & this -> authKeyIdentifier ) ;
 this -> authKeyIdentifier = x509_parse_authorityKeyIdentifier ( object , level , & this -> authKeySerialNumber ) ;
 break ;
 case OID_AUTHORITY_INFO_ACCESS : if ( ! parse_authorityInfoAccess ( object , level , this ) ) {
 goto end ;
 }
 break ;
 case OID_KEY_USAGE : parse_keyUsage ( object , this ) ;
 break ;
 case OID_EXTENDED_KEY_USAGE : if ( ! parse_extendedKeyUsage ( object , level , this ) ) {
 goto end ;
 }
 break ;
 case OID_IP_ADDR_BLOCKS : if ( ! parse_ipAddrBlocks ( object , level , this ) ) {
 goto end ;
 }
 break ;
 case OID_NAME_CONSTRAINTS : if ( ! parse_nameConstraints ( object , level , this ) ) {
 goto end ;
 }
 break ;
 case OID_CERTIFICATE_POLICIES : if ( ! parse_certificatePolicies ( object , level , this ) ) {
 goto end ;
 }
 break ;
 case OID_POLICY_MAPPINGS : if ( ! parse_policyMappings ( object , level , this ) ) {
 goto end ;
 }
 break ;
 case OID_POLICY_CONSTRAINTS : if ( ! parse_policyConstraints ( object , level , this ) ) {
 goto end ;
 }
 break ;
 case OID_INHIBIT_ANY_POLICY : if ( ! asn1_parse_simple_object ( & object , ASN1_INTEGER , level , "inhibitAnyPolicy" ) ) {
 goto end ;
 }
 this -> inhibit_any = parse_constraint ( object ) ;
 break ;
 case OID_NS_REVOCATION_URL : case OID_NS_CA_REVOCATION_URL : case OID_NS_CA_POLICY_URL : case OID_NS_COMMENT : if ( ! asn1_parse_simple_object ( & object , ASN1_IA5STRING , level , oid_names [ extn_oid ] . name ) ) {
 goto end ;
 }
 break ;
 default : if ( critical && lib -> settings -> get_bool ( lib -> settings , "%s.x509.enforce_critical" , TRUE , lib -> ns ) ) {
 DBG1 ( DBG_ASN , "critical '%s' extension not supported" , ( extn_oid == OID_UNKNOWN ) ? "unknown" : ( char * ) oid_names [ extn_oid ] . name ) ;
 goto end ;
 }
 break ;
 }
 break ;
 }
 case X509_OBJ_ALGORITHM : this -> algorithm = asn1_parse_algorithmIdentifier ( object , level , NULL ) ;
 if ( this -> algorithm != sig_alg ) {
 DBG1 ( DBG_ASN , " signature algorithms do not agree" ) ;
 goto end ;
 }
 break ;
 case X509_OBJ_SIGNATURE : this -> signature = chunk_skip ( object , 1 ) ;
 break ;
 default : break ;
 }
 }
 success = parser -> success ( parser ) ;
 end : parser -> destroy ( parser ) ;
 if ( success ) {
 hasher_t * hasher ;
 if ( this -> public . interface . interface . issued_by ( & this -> public . interface . interface , & this -> public . interface . interface , NULL ) ) {
 this -> flags |= X509_SELF_SIGNED ;
 }
 hasher = lib -> crypto -> create_hasher ( lib -> crypto , HASH_SHA1 ) ;
 if ( ! hasher || ! hasher -> allocate_hash ( hasher , this -> encoding , & this -> encoding_hash ) ) {
 DESTROY_IF ( hasher ) ;
 DBG1 ( DBG_ASN , " unable to create hash of certificate, SHA1 not supported" ) ;
 return FALSE ;
 }
 hasher -> destroy ( hasher ) ;
 }
 return success ;
 }