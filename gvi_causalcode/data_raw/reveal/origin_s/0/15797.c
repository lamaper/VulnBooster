void kadmin_setstring ( int argc , char * argv [ ] ) {
 kadm5_ret_t retval ;
 char * pname , * canon = NULL , * key , * value ;
 krb5_principal princ = NULL ;
 if ( argc != 4 ) {
 fprintf ( stderr , _ ( "usage: set_string principal key value\n" ) ) ;
 return ;
 }
 pname = argv [ 1 ] ;
 key = argv [ 2 ] ;
 value = argv [ 3 ] ;
 retval = kadmin_parse_name ( pname , & princ ) ;
 if ( retval ) {
 com_err ( "set_string" , retval , _ ( "while parsing principal" ) ) ;
 return ;
 }
 retval = krb5_unparse_name ( context , princ , & canon ) ;
 if ( retval ) {
 com_err ( "set_string" , retval , _ ( "while canonicalizing principal" ) ) ;
 goto cleanup ;
 }
 retval = kadm5_set_string ( handle , princ , key , value ) ;
 if ( retval ) {
 com_err ( "set_string" , retval , _ ( "while setting attribute on principal \"%s\"" ) , canon ) ;
 goto cleanup ;
 }
 printf ( _ ( "Attribute set for principal \"%s\".\n" ) , canon ) ;
 cleanup : krb5_free_principal ( context , princ ) ;
 free ( canon ) ;
 return ;
 }