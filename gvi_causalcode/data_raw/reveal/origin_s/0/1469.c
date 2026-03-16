static void add_cdps ( linked_list_t * list , linked_list_t * uris , linked_list_t * issuers ) {
 identification_t * issuer , * id ;
 enumerator_t * enumerator ;
 x509_cdp_t * cdp ;
 char * uri ;
 while ( uris -> remove_last ( uris , ( void * * ) & id ) == SUCCESS ) {
 if ( gn_to_string ( id , & uri ) ) {
 if ( issuers -> get_count ( issuers ) ) {
 enumerator = issuers -> create_enumerator ( issuers ) ;
 while ( enumerator -> enumerate ( enumerator , & issuer ) ) {
 INIT ( cdp , . uri = strdup ( uri ) , . issuer = issuer -> clone ( issuer ) , ) ;
 list -> insert_last ( list , cdp ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 free ( uri ) ;
 }
 else {
 INIT ( cdp , . uri = uri , ) ;
 list -> insert_last ( list , cdp ) ;
 }
 }
 id -> destroy ( id ) ;
 }
 while ( issuers -> remove_last ( issuers , ( void * * ) & id ) == SUCCESS ) {
 id -> destroy ( id ) ;
 }
 }