void kadmin_delstring ( int argc , char * argv [ ] ) {
 kadm5_ret_t retval ;
 char * pname , * canon = NULL , * key ;
 krb5_principal princ = NULL ;
 if ( argc != 3 ) {
 fprintf ( stderr , _ ( "usage: del_string principal key\n" ) ) ;
 return ;
 }
 pname = argv [ 1 ] ;
 key = argv [ 2 ] ;
 retval = kadmin_parse_name ( pname , & princ ) ;
 if ( retval ) {
 com_err ( "delstring" , retval , _ ( "while parsing principal" ) ) ;
 return ;
 }
 retval = krb5_unparse_name ( context , princ , & canon ) ;
 if ( retval ) {
 com_err ( "del_string" , retval , _ ( "while canonicalizing principal" ) ) ;
 goto cleanup ;
 }
 retval = kadm5_set_string ( handle , princ , key , NULL ) ;
 if ( retval ) {
 com_err ( "del_string" , retval , _ ( "while deleting attribute from principal \"%s\"" ) , canon ) ;
 goto cleanup ;
 }
 printf ( _ ( "Attribute removed from principal \"%s\".\n" ) , canon ) ;
 cleanup : krb5_free_principal ( context , princ ) ;
 free ( canon ) ;
 return ;
 }