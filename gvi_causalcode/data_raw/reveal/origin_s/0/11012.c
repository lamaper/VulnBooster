METHOD ( certificate_t , destroy , void , private_x509_cert_t * this ) {
 if ( ref_put ( & this -> ref ) ) {
 this -> subjectAltNames -> destroy_offset ( this -> subjectAltNames , offsetof ( identification_t , destroy ) ) ;
 this -> crl_uris -> destroy_function ( this -> crl_uris , ( void * ) crl_uri_destroy ) ;
 this -> ocsp_uris -> destroy_function ( this -> ocsp_uris , free ) ;
 this -> ipAddrBlocks -> destroy_offset ( this -> ipAddrBlocks , offsetof ( traffic_selector_t , destroy ) ) ;
 this -> permitted_names -> destroy_offset ( this -> permitted_names , offsetof ( identification_t , destroy ) ) ;
 this -> excluded_names -> destroy_offset ( this -> excluded_names , offsetof ( identification_t , destroy ) ) ;
 this -> cert_policies -> destroy_function ( this -> cert_policies , ( void * ) cert_policy_destroy ) ;
 this -> policy_mappings -> destroy_function ( this -> policy_mappings , ( void * ) policy_mapping_destroy ) ;
 DESTROY_IF ( this -> issuer ) ;
 DESTROY_IF ( this -> subject ) ;
 DESTROY_IF ( this -> public_key ) ;
 chunk_free ( & this -> authKeyIdentifier ) ;
 chunk_free ( & this -> encoding ) ;
 chunk_free ( & this -> encoding_hash ) ;
 if ( ! this -> parsed ) {
 chunk_free ( & this -> signature ) ;
 chunk_free ( & this -> serialNumber ) ;
 chunk_free ( & this -> tbsCertificate ) ;
 }
 free ( this ) ;
 }
 }