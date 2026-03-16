void kadmin_purgekeys ( int argc , char * argv [ ] ) {
 kadm5_ret_t retval ;
 int keepkvno = - 1 ;
 char * pname = NULL , * canon = NULL ;
 krb5_principal princ ;
 if ( argc == 4 && strcmp ( argv [ 1 ] , "-keepkvno" ) == 0 ) {
 keepkvno = atoi ( argv [ 2 ] ) ;
 pname = argv [ 3 ] ;
 }
 if ( argc == 2 ) {
 pname = argv [ 1 ] ;
 }
 if ( pname == NULL ) {
 fprintf ( stderr , _ ( "usage: purgekeys [-keepkvno oldest_kvno_to_keep] " "principal\n" ) ) ;
 return ;
 }
 retval = kadmin_parse_name ( pname , & princ ) ;
 if ( retval ) {
 com_err ( "purgekeys" , retval , _ ( "while parsing principal" ) ) ;
 return ;
 }
 retval = krb5_unparse_name ( context , princ , & canon ) ;
 if ( retval ) {
 com_err ( "purgekeys" , retval , _ ( "while canonicalizing principal" ) ) ;
 goto cleanup ;
 }
 retval = kadm5_purgekeys ( handle , princ , keepkvno ) ;
 if ( retval ) {
 com_err ( "purgekeys" , retval , _ ( "while purging keys for principal \"%s\"" ) , canon ) ;
 goto cleanup ;
 }
 printf ( _ ( "Old keys for principal \"%s\" purged.\n" ) , canon ) ;
 cleanup : krb5_free_principal ( context , princ ) ;
 free ( canon ) ;
 return ;
 }