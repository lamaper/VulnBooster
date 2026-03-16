static QCryptoTLSCreds * nbd_get_tls_creds ( const char * id , Error * * errp ) {
 Object * obj ;
 QCryptoTLSCreds * creds ;
 obj = object_resolve_path_component ( object_get_objects_root ( ) , id ) ;
 if ( ! obj ) {
 error_setg ( errp , "No TLS credentials with id '%s'" , id ) ;
 return NULL ;
 }
 creds = ( QCryptoTLSCreds * ) object_dynamic_cast ( obj , TYPE_QCRYPTO_TLS_CREDS ) ;
 if ( ! creds ) {
 error_setg ( errp , "Object with id '%s' is not TLS credentials" , id ) ;
 return NULL ;
 }
 if ( creds -> endpoint != QCRYPTO_TLS_CREDS_ENDPOINT_SERVER ) {
 error_setg ( errp , "Expecting TLS credentials with a server endpoint" ) ;
 return NULL ;
 }
 object_ref ( obj ) ;
 return creds ;
 }