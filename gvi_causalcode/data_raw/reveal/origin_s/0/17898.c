x509_cert_t * x509_cert_gen ( certificate_type_t type , va_list args ) {
 private_x509_cert_t * cert ;
 certificate_t * sign_cert = NULL ;
 private_key_t * sign_key = NULL ;
 hash_algorithm_t digest_alg = HASH_SHA1 ;
 u_int constraint ;
 cert = create_empty ( ) ;
 while ( TRUE ) {
 switch ( va_arg ( args , builder_part_t ) ) {
 case BUILD_X509_FLAG : cert -> flags |= va_arg ( args , x509_flag_t ) ;
 continue ;
 case BUILD_SIGNING_KEY : sign_key = va_arg ( args , private_key_t * ) ;
 continue ;
 case BUILD_SIGNING_CERT : sign_cert = va_arg ( args , certificate_t * ) ;
 continue ;
 case BUILD_PUBLIC_KEY : cert -> public_key = va_arg ( args , public_key_t * ) ;
 cert -> public_key -> get_ref ( cert -> public_key ) ;
 continue ;
 case BUILD_SUBJECT : cert -> subject = va_arg ( args , identification_t * ) ;
 cert -> subject = cert -> subject -> clone ( cert -> subject ) ;
 continue ;
 case BUILD_SUBJECT_ALTNAMES : {
 enumerator_t * enumerator ;
 identification_t * id ;
 linked_list_t * list ;
 list = va_arg ( args , linked_list_t * ) ;
 enumerator = list -> create_enumerator ( list ) ;
 while ( enumerator -> enumerate ( enumerator , & id ) ) {
 cert -> subjectAltNames -> insert_last ( cert -> subjectAltNames , id -> clone ( id ) ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 continue ;
 }
 case BUILD_CRL_DISTRIBUTION_POINTS : {
 enumerator_t * enumerator ;
 linked_list_t * list ;
 x509_cdp_t * in , * cdp ;
 list = va_arg ( args , linked_list_t * ) ;
 enumerator = list -> create_enumerator ( list ) ;
 while ( enumerator -> enumerate ( enumerator , & in ) ) {
 INIT ( cdp , . uri = strdup ( in -> uri ) , . issuer = in -> issuer ? in -> issuer -> clone ( in -> issuer ) : NULL , ) ;
 cert -> crl_uris -> insert_last ( cert -> crl_uris , cdp ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 continue ;
 }
 case BUILD_OCSP_ACCESS_LOCATIONS : {
 enumerator_t * enumerator ;
 linked_list_t * list ;
 char * uri ;
 list = va_arg ( args , linked_list_t * ) ;
 enumerator = list -> create_enumerator ( list ) ;
 while ( enumerator -> enumerate ( enumerator , & uri ) ) {
 cert -> ocsp_uris -> insert_last ( cert -> ocsp_uris , strdup ( uri ) ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 continue ;
 }
 case BUILD_PATHLEN : constraint = va_arg ( args , u_int ) ;
 cert -> pathLenConstraint = ( constraint < 128 ) ? constraint : X509_NO_CONSTRAINT ;
 continue ;
 case BUILD_ADDRBLOCKS : {
 enumerator_t * enumerator ;
 traffic_selector_t * ts ;
 linked_list_t * list ;
 list = va_arg ( args , linked_list_t * ) ;
 enumerator = list -> create_enumerator ( list ) ;
 while ( enumerator -> enumerate ( enumerator , & ts ) ) {
 cert -> ipAddrBlocks -> insert_last ( cert -> ipAddrBlocks , ts -> clone ( ts ) ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 continue ;
 }
 case BUILD_PERMITTED_NAME_CONSTRAINTS : {
 enumerator_t * enumerator ;
 linked_list_t * list ;
 identification_t * constraint ;
 list = va_arg ( args , linked_list_t * ) ;
 enumerator = list -> create_enumerator ( list ) ;
 while ( enumerator -> enumerate ( enumerator , & constraint ) ) {
 cert -> permitted_names -> insert_last ( cert -> permitted_names , constraint -> clone ( constraint ) ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 continue ;
 }
 case BUILD_EXCLUDED_NAME_CONSTRAINTS : {
 enumerator_t * enumerator ;
 linked_list_t * list ;
 identification_t * constraint ;
 list = va_arg ( args , linked_list_t * ) ;
 enumerator = list -> create_enumerator ( list ) ;
 while ( enumerator -> enumerate ( enumerator , & constraint ) ) {
 cert -> excluded_names -> insert_last ( cert -> excluded_names , constraint -> clone ( constraint ) ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 continue ;
 }
 case BUILD_CERTIFICATE_POLICIES : {
 enumerator_t * enumerator ;
 linked_list_t * list ;
 x509_cert_policy_t * policy , * in ;
 list = va_arg ( args , linked_list_t * ) ;
 enumerator = list -> create_enumerator ( list ) ;
 while ( enumerator -> enumerate ( enumerator , & in ) ) {
 INIT ( policy , . oid = chunk_clone ( in -> oid ) , . cps_uri = strdupnull ( in -> cps_uri ) , . unotice_text = strdupnull ( in -> unotice_text ) , ) ;
 cert -> cert_policies -> insert_last ( cert -> cert_policies , policy ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 continue ;
 }
 case BUILD_POLICY_MAPPINGS : {
 enumerator_t * enumerator ;
 linked_list_t * list ;
 x509_policy_mapping_t * mapping , * in ;
 list = va_arg ( args , linked_list_t * ) ;
 enumerator = list -> create_enumerator ( list ) ;
 while ( enumerator -> enumerate ( enumerator , & in ) ) {
 INIT ( mapping , . issuer = chunk_clone ( in -> issuer ) , . subject = chunk_clone ( in -> subject ) , ) ;
 cert -> policy_mappings -> insert_last ( cert -> policy_mappings , mapping ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 continue ;
 }
 case BUILD_POLICY_REQUIRE_EXPLICIT : constraint = va_arg ( args , u_int ) ;
 cert -> require_explicit = ( constraint < 128 ) ? constraint : X509_NO_CONSTRAINT ;
 continue ;
 case BUILD_POLICY_INHIBIT_MAPPING : constraint = va_arg ( args , u_int ) ;
 cert -> inhibit_mapping = ( constraint < 128 ) ? constraint : X509_NO_CONSTRAINT ;
 continue ;
 case BUILD_POLICY_INHIBIT_ANY : constraint = va_arg ( args , u_int ) ;
 cert -> inhibit_any = ( constraint < 128 ) ? constraint : X509_NO_CONSTRAINT ;
 continue ;
 case BUILD_NOT_BEFORE_TIME : cert -> notBefore = va_arg ( args , time_t ) ;
 continue ;
 case BUILD_NOT_AFTER_TIME : cert -> notAfter = va_arg ( args , time_t ) ;
 continue ;
 case BUILD_SERIAL : cert -> serialNumber = chunk_clone ( va_arg ( args , chunk_t ) ) ;
 continue ;
 case BUILD_DIGEST_ALG : digest_alg = va_arg ( args , int ) ;
 continue ;
 case BUILD_END : break ;
 default : destroy ( cert ) ;
 return NULL ;
 }
 break ;
 }
 if ( sign_key && generate ( cert , sign_cert , sign_key , digest_alg ) ) {
 return & cert -> public ;
 }
 destroy ( cert ) ;
 return NULL ;
 }