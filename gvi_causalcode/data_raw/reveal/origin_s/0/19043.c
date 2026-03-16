static bool generate ( private_x509_cert_t * cert , certificate_t * sign_cert , private_key_t * sign_key , int digest_alg ) {
 chunk_t extensions = chunk_empty , extendedKeyUsage = chunk_empty ;
 chunk_t serverAuth = chunk_empty , clientAuth = chunk_empty ;
 chunk_t ocspSigning = chunk_empty , certPolicies = chunk_empty ;
 chunk_t basicConstraints = chunk_empty , nameConstraints = chunk_empty ;
 chunk_t keyUsage = chunk_empty , keyUsageBits = chunk_empty ;
 chunk_t subjectAltNames = chunk_empty , policyMappings = chunk_empty ;
 chunk_t subjectKeyIdentifier = chunk_empty , authKeyIdentifier = chunk_empty ;
 chunk_t crlDistributionPoints = chunk_empty , authorityInfoAccess = chunk_empty ;
 chunk_t policyConstraints = chunk_empty , inhibitAnyPolicy = chunk_empty ;
 chunk_t ikeIntermediate = chunk_empty , msSmartcardLogon = chunk_empty ;
 chunk_t ipAddrBlocks = chunk_empty ;
 identification_t * issuer , * subject ;
 chunk_t key_info ;
 signature_scheme_t scheme ;
 hasher_t * hasher ;
 enumerator_t * enumerator ;
 char * uri ;
 subject = cert -> subject ;
 if ( sign_cert ) {
 issuer = sign_cert -> get_subject ( sign_cert ) ;
 if ( ! cert -> public_key ) {
 return FALSE ;
 }
 }
 else {
 issuer = subject ;
 if ( ! cert -> public_key ) {
 cert -> public_key = sign_key -> get_public_key ( sign_key ) ;
 }
 cert -> flags |= X509_SELF_SIGNED ;
 }
 cert -> issuer = issuer -> clone ( issuer ) ;
 if ( ! cert -> notBefore ) {
 cert -> notBefore = time ( NULL ) ;
 }
 if ( ! cert -> notAfter ) {
 cert -> notAfter = cert -> notBefore + 60 * 60 * 24 * 365 ;
 }
 cert -> algorithm = hasher_signature_algorithm_to_oid ( digest_alg , sign_key -> get_type ( sign_key ) ) ;
 if ( cert -> algorithm == OID_UNKNOWN ) {
 return FALSE ;
 }
 scheme = signature_scheme_from_oid ( cert -> algorithm ) ;
 if ( ! cert -> public_key -> get_encoding ( cert -> public_key , PUBKEY_SPKI_ASN1_DER , & key_info ) ) {
 return FALSE ;
 }
 subjectAltNames = x509_build_subjectAltNames ( cert -> subjectAltNames ) ;
 crlDistributionPoints = x509_build_crlDistributionPoints ( cert -> crl_uris , OID_CRL_DISTRIBUTION_POINTS ) ;
 enumerator = cert -> ocsp_uris -> create_enumerator ( cert -> ocsp_uris ) ;
 while ( enumerator -> enumerate ( enumerator , & uri ) ) {
 chunk_t accessDescription ;
 accessDescription = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( OID_OCSP ) , asn1_wrap ( ASN1_CONTEXT_S_6 , "c" , chunk_create ( uri , strlen ( uri ) ) ) ) ;
 authorityInfoAccess = chunk_cat ( "mm" , authorityInfoAccess , accessDescription ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 if ( authorityInfoAccess . ptr ) {
 authorityInfoAccess = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( OID_AUTHORITY_INFO_ACCESS ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_SEQUENCE , "m" , authorityInfoAccess ) ) ) ;
 }
 if ( cert -> flags & X509_CA ) {
 chunk_t pathLenConstraint = chunk_empty ;
 if ( cert -> pathLenConstraint != X509_NO_CONSTRAINT ) {
 pathLenConstraint = asn1_integer ( "c" , chunk_from_thing ( cert -> pathLenConstraint ) ) ;
 }
 basicConstraints = asn1_wrap ( ASN1_SEQUENCE , "mmm" , asn1_build_known_oid ( OID_BASIC_CONSTRAINTS ) , asn1_wrap ( ASN1_BOOLEAN , "c" , chunk_from_chars ( 0xFF ) ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_wrap ( ASN1_BOOLEAN , "c" , chunk_from_chars ( 0xFF ) ) , pathLenConstraint ) ) ) ;
 keyUsageBits = chunk_from_chars ( 0x01 , 0x06 ) ;
 }
 else if ( cert -> flags & X509_CRL_SIGN ) {
 keyUsageBits = chunk_from_chars ( 0x01 , 0x02 ) ;
 }
 if ( keyUsageBits . len ) {
 keyUsage = asn1_wrap ( ASN1_SEQUENCE , "mmm" , asn1_build_known_oid ( OID_KEY_USAGE ) , asn1_wrap ( ASN1_BOOLEAN , "c" , chunk_from_chars ( 0xFF ) ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_BIT_STRING , "c" , keyUsageBits ) ) ) ;
 }
 if ( cert -> flags & X509_SERVER_AUTH ) {
 serverAuth = asn1_build_known_oid ( OID_SERVER_AUTH ) ;
 }
 if ( cert -> flags & X509_CLIENT_AUTH ) {
 clientAuth = asn1_build_known_oid ( OID_CLIENT_AUTH ) ;
 }
 if ( cert -> flags & X509_IKE_INTERMEDIATE ) {
 ikeIntermediate = asn1_build_known_oid ( OID_IKE_INTERMEDIATE ) ;
 }
 if ( cert -> flags & X509_OCSP_SIGNER ) {
 ocspSigning = asn1_build_known_oid ( OID_OCSP_SIGNING ) ;
 }
 if ( cert -> flags & X509_MS_SMARTCARD_LOGON ) {
 msSmartcardLogon = asn1_build_known_oid ( OID_MS_SMARTCARD_LOGON ) ;
 }
 if ( serverAuth . ptr || clientAuth . ptr || ikeIntermediate . ptr || ocspSigning . ptr || msSmartcardLogon . ptr ) {
 extendedKeyUsage = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( OID_EXTENDED_KEY_USAGE ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_SEQUENCE , "mmmmm" , serverAuth , clientAuth , ikeIntermediate , ocspSigning , msSmartcardLogon ) ) ) ;
 }
 if ( cert -> flags & ( X509_CA | X509_OCSP_SIGNER | X509_CRL_SIGN ) ) {
 chunk_t keyid ;
 if ( cert -> public_key -> get_fingerprint ( cert -> public_key , KEYID_PUBKEY_SHA1 , & keyid ) ) {
 subjectKeyIdentifier = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( OID_SUBJECT_KEY_ID ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_OCTET_STRING , "c" , keyid ) ) ) ;
 }
 }
 if ( sign_cert ) {
 chunk_t keyid ;
 if ( sign_key -> get_fingerprint ( sign_key , KEYID_PUBKEY_SHA1 , & keyid ) ) {
 authKeyIdentifier = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( OID_AUTHORITY_KEY_ID ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_SEQUENCE , "m" , asn1_wrap ( ASN1_CONTEXT_S_0 , "c" , keyid ) ) ) ) ;
 }
 }
 if ( cert -> ipAddrBlocks -> get_count ( cert -> ipAddrBlocks ) ) {
 chunk_t v4blocks = chunk_empty , v6blocks = chunk_empty , block ;
 traffic_selector_t * ts ;
 enumerator = cert -> ipAddrBlocks -> create_enumerator ( cert -> ipAddrBlocks ) ;
 while ( enumerator -> enumerate ( enumerator , & ts ) ) {
 switch ( ts -> get_type ( ts ) ) {
 case TS_IPV4_ADDR_RANGE : block = generate_ts ( ts ) ;
 v4blocks = chunk_cat ( "mm" , v4blocks , block ) ;
 break ;
 case TS_IPV6_ADDR_RANGE : block = generate_ts ( ts ) ;
 v6blocks = chunk_cat ( "mm" , v6blocks , block ) ;
 break ;
 default : break ;
 }
 }
 enumerator -> destroy ( enumerator ) ;
 if ( v4blocks . ptr ) {
 v4blocks = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_wrap ( ASN1_OCTET_STRING , "c" , chunk_from_chars ( 0x00 , 0x01 ) ) , asn1_wrap ( ASN1_SEQUENCE , "m" , v4blocks ) ) ;
 }
 if ( v6blocks . ptr ) {
 v6blocks = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_wrap ( ASN1_OCTET_STRING , "c" , chunk_from_chars ( 0x00 , 0x02 ) ) , asn1_wrap ( ASN1_SEQUENCE , "m" , v6blocks ) ) ;
 }
 ipAddrBlocks = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( OID_IP_ADDR_BLOCKS ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_SEQUENCE , "mm" , v4blocks , v6blocks ) ) ) ;
 cert -> flags |= X509_IP_ADDR_BLOCKS ;
 }
 if ( cert -> permitted_names -> get_count ( cert -> permitted_names ) || cert -> excluded_names -> get_count ( cert -> excluded_names ) ) {
 chunk_t permitted = chunk_empty , excluded = chunk_empty , subtree ;
 identification_t * id ;
 enumerator = create_name_constraint_enumerator ( cert , TRUE ) ;
 while ( enumerator -> enumerate ( enumerator , & id ) ) {
 subtree = asn1_wrap ( ASN1_SEQUENCE , "m" , build_generalName ( id ) ) ;
 permitted = chunk_cat ( "mm" , permitted , subtree ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 if ( permitted . ptr ) {
 permitted = asn1_wrap ( ASN1_CONTEXT_C_0 , "m" , permitted ) ;
 }
 enumerator = create_name_constraint_enumerator ( cert , FALSE ) ;
 while ( enumerator -> enumerate ( enumerator , & id ) ) {
 subtree = asn1_wrap ( ASN1_SEQUENCE , "m" , build_generalName ( id ) ) ;
 excluded = chunk_cat ( "mm" , excluded , subtree ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 if ( excluded . ptr ) {
 excluded = asn1_wrap ( ASN1_CONTEXT_C_1 , "m" , excluded ) ;
 }
 nameConstraints = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( OID_NAME_CONSTRAINTS ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_SEQUENCE , "mm" , permitted , excluded ) ) ) ;
 }
 if ( cert -> cert_policies -> get_count ( cert -> cert_policies ) ) {
 x509_cert_policy_t * policy ;
 enumerator = create_cert_policy_enumerator ( cert ) ;
 while ( enumerator -> enumerate ( enumerator , & policy ) ) {
 chunk_t chunk = chunk_empty , cps = chunk_empty , notice = chunk_empty ;
 if ( policy -> cps_uri ) {
 cps = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( OID_POLICY_QUALIFIER_CPS ) , asn1_wrap ( ASN1_IA5STRING , "c" , chunk_create ( policy -> cps_uri , strlen ( policy -> cps_uri ) ) ) ) ;
 }
 if ( policy -> unotice_text ) {
 notice = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( OID_POLICY_QUALIFIER_UNOTICE ) , asn1_wrap ( ASN1_SEQUENCE , "m" , asn1_wrap ( ASN1_VISIBLESTRING , "c" , chunk_create ( policy -> unotice_text , strlen ( policy -> unotice_text ) ) ) ) ) ;
 }
 if ( cps . len || notice . len ) {
 chunk = asn1_wrap ( ASN1_SEQUENCE , "mm" , cps , notice ) ;
 }
 chunk = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_wrap ( ASN1_OID , "c" , policy -> oid ) , chunk ) ;
 certPolicies = chunk_cat ( "mm" , certPolicies , chunk ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 certPolicies = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( OID_CERTIFICATE_POLICIES ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_SEQUENCE , "m" , certPolicies ) ) ) ;
 }
 if ( cert -> policy_mappings -> get_count ( cert -> policy_mappings ) ) {
 x509_policy_mapping_t * mapping ;
 enumerator = create_policy_mapping_enumerator ( cert ) ;
 while ( enumerator -> enumerate ( enumerator , & mapping ) ) {
 chunk_t chunk ;
 chunk = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_wrap ( ASN1_OID , "c" , mapping -> issuer ) , asn1_wrap ( ASN1_OID , "c" , mapping -> subject ) ) ;
 policyMappings = chunk_cat ( "mm" , policyMappings , chunk ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 policyMappings = asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( OID_POLICY_MAPPINGS ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_SEQUENCE , "m" , policyMappings ) ) ) ;
 }
 if ( cert -> inhibit_mapping != X509_NO_CONSTRAINT || cert -> require_explicit != X509_NO_CONSTRAINT ) {
 chunk_t inhibit = chunk_empty , explicit = chunk_empty ;
 if ( cert -> require_explicit != X509_NO_CONSTRAINT ) {
 explicit = asn1_wrap ( ASN1_CONTEXT_C_0 , "m" , asn1_integer ( "c" , chunk_from_thing ( cert -> require_explicit ) ) ) ;
 }
 if ( cert -> inhibit_mapping != X509_NO_CONSTRAINT ) {
 inhibit = asn1_wrap ( ASN1_CONTEXT_C_1 , "m" , asn1_integer ( "c" , chunk_from_thing ( cert -> inhibit_mapping ) ) ) ;
 }
 policyConstraints = asn1_wrap ( ASN1_SEQUENCE , "mmm" , asn1_build_known_oid ( OID_POLICY_CONSTRAINTS ) , asn1_wrap ( ASN1_BOOLEAN , "c" , chunk_from_chars ( 0xFF ) ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_SEQUENCE , "mm" , explicit , inhibit ) ) ) ;
 }
 if ( cert -> inhibit_any != X509_NO_CONSTRAINT ) {
 inhibitAnyPolicy = asn1_wrap ( ASN1_SEQUENCE , "mmm" , asn1_build_known_oid ( OID_INHIBIT_ANY_POLICY ) , asn1_wrap ( ASN1_BOOLEAN , "c" , chunk_from_chars ( 0xFF ) ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_integer ( "c" , chunk_from_thing ( cert -> inhibit_any ) ) ) ) ;
 }
 if ( basicConstraints . ptr || subjectAltNames . ptr || authKeyIdentifier . ptr || crlDistributionPoints . ptr || nameConstraints . ptr || ipAddrBlocks . ptr ) {
 extensions = asn1_wrap ( ASN1_CONTEXT_C_3 , "m" , asn1_wrap ( ASN1_SEQUENCE , "mmmmmmmmmmmmmm" , basicConstraints , keyUsage , subjectKeyIdentifier , authKeyIdentifier , subjectAltNames , extendedKeyUsage , crlDistributionPoints , authorityInfoAccess , nameConstraints , certPolicies , policyMappings , policyConstraints , inhibitAnyPolicy , ipAddrBlocks ) ) ;
 }
 cert -> tbsCertificate = asn1_wrap ( ASN1_SEQUENCE , "mmmcmcmm" , asn1_simple_object ( ASN1_CONTEXT_C_0 , ASN1_INTEGER_2 ) , asn1_integer ( "c" , cert -> serialNumber ) , asn1_algorithmIdentifier ( cert -> algorithm ) , issuer -> get_encoding ( issuer ) , asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_from_time ( & cert -> notBefore , ASN1_UTCTIME ) , asn1_from_time ( & cert -> notAfter , ASN1_UTCTIME ) ) , subject -> get_encoding ( subject ) , key_info , extensions ) ;
 if ( ! sign_key -> sign ( sign_key , scheme , cert -> tbsCertificate , & cert -> signature ) ) {
 return FALSE ;
 }
 cert -> encoding = asn1_wrap ( ASN1_SEQUENCE , "cmm" , cert -> tbsCertificate , asn1_algorithmIdentifier ( cert -> algorithm ) , asn1_bitstring ( "c" , cert -> signature ) ) ;
 hasher = lib -> crypto -> create_hasher ( lib -> crypto , HASH_SHA1 ) ;
 if ( ! hasher || ! hasher -> allocate_hash ( hasher , cert -> encoding , & cert -> encoding_hash ) ) {
 DESTROY_IF ( hasher ) ;
 return FALSE ;
 }
 hasher -> destroy ( hasher ) ;
 return TRUE ;
 }