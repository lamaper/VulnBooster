void kadmin_getstrings ( int argc , char * argv [ ] ) {
 kadm5_ret_t retval ;
 char * pname , * canon = NULL ;
 krb5_principal princ = NULL ;
 krb5_string_attr * strings = NULL ;
 int count , i ;
 if ( argc != 2 ) {
 fprintf ( stderr , _ ( "usage: get_strings principal\n" ) ) ;
 return ;
 }
 pname = argv [ 1 ] ;
 retval = kadmin_parse_name ( pname , & princ ) ;
 if ( retval ) {
 com_err ( "get_strings" , retval , _ ( "while parsing principal" ) ) ;
 return ;
 }
 retval = krb5_unparse_name ( context , princ , & canon ) ;
 if ( retval ) {
 com_err ( "get_strings" , retval , _ ( "while canonicalizing principal" ) ) ;
 goto cleanup ;
 }
 retval = kadm5_get_strings ( handle , princ , & strings , & count ) ;
 if ( retval ) {
 com_err ( "get_strings" , retval , _ ( "while getting attributes for principal \"%s\"" ) , canon ) ;
 goto cleanup ;
 }
 if ( count == 0 ) printf ( _ ( "(No string attributes.)\n" ) ) ;
 for ( i = 0 ;
 i < count ;
 i ++ ) printf ( "%s: %s\n" , strings [ i ] . key , strings [ i ] . value ) ;
 kadm5_free_strings ( handle , strings , count ) ;
 cleanup : krb5_free_principal ( context , princ ) ;
 free ( canon ) ;
 return ;
 }