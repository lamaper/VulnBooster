void kadmin_delprinc ( int argc , char * argv [ ] ) {
 kadm5_ret_t retval ;
 krb5_principal princ = NULL ;
 char * canon = NULL ;
 char reply [ 5 ] ;
 if ( ! ( argc == 2 || ( argc == 3 && ! strcmp ( "-force" , argv [ 1 ] ) ) ) ) {
 fprintf ( stderr , _ ( "usage: delete_principal [-force] principal\n" ) ) ;
 return ;
 }
 retval = kadmin_parse_name ( argv [ argc - 1 ] , & princ ) ;
 if ( retval ) {
 com_err ( "delete_principal" , retval , _ ( "while parsing principal name" ) ) ;
 return ;
 }
 retval = krb5_unparse_name ( context , princ , & canon ) ;
 if ( retval ) {
 com_err ( "delete_principal" , retval , _ ( "while canonicalizing principal" ) ) ;
 goto cleanup ;
 }
 if ( argc == 2 ) {
 printf ( _ ( "Are you sure you want to delete the principal \"%s\"? " "(yeso): " ) , canon ) ;
 fgets ( reply , sizeof ( reply ) , stdin ) ;
 if ( strcmp ( "yes\n" , reply ) ) {
 fprintf ( stderr , _ ( "Principal \"%s\" not deleted\n" ) , canon ) ;
 goto cleanup ;
 }
 }
 retval = kadm5_delete_principal ( handle , princ ) ;
 if ( retval ) {
 com_err ( "delete_principal" , retval , _ ( "while deleting principal \"%s\"" ) , canon ) ;
 goto cleanup ;
 }
 printf ( _ ( "Principal \"%s\" deleted.\n" ) , canon ) ;
 printf ( _ ( "Make sure that you have removed this principal from all ACLs " "before reusing.\n" ) ) ;
 cleanup : krb5_free_principal ( context , princ ) ;
 free ( canon ) ;
 }