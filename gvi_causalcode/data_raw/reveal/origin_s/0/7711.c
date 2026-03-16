x509_cert_t * x509_cert_load ( certificate_type_t type , va_list args ) {
 x509_flag_t flags = 0 ;
 chunk_t blob = chunk_empty ;
 while ( TRUE ) {
 switch ( va_arg ( args , builder_part_t ) ) {
 case BUILD_BLOB_ASN1_DER : blob = va_arg ( args , chunk_t ) ;
 continue ;
 case BUILD_X509_FLAG : flags |= va_arg ( args , x509_flag_t ) ;
 continue ;
 case BUILD_END : break ;
 default : return NULL ;
 }
 break ;
 }
 if ( blob . ptr ) {
 private_x509_cert_t * cert = create_empty ( ) ;
 cert -> encoding = chunk_clone ( blob ) ;
 cert -> parsed = TRUE ;
 if ( parse_certificate ( cert ) ) {
 cert -> flags |= flags ;
 return & cert -> public ;
 }
 destroy ( cert ) ;
 }
 return NULL ;
 }