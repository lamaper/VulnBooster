void kadmin_renameprinc ( int argc , char * argv [ ] ) {
 kadm5_ret_t retval ;
 krb5_principal oprinc = NULL , nprinc = NULL ;
 char * ocanon = NULL , * ncanon = NULL ;
 char reply [ 5 ] ;
 if ( ! ( argc == 3 || ( argc == 4 && ! strcmp ( "-force" , argv [ 1 ] ) ) ) ) {
 fprintf ( stderr , _ ( "usage: rename_principal [-force] old_principal " "new_principal\n" ) ) ;
 return ;
 }
 retval = kadmin_parse_name ( argv [ argc - 2 ] , & oprinc ) ;
 if ( retval ) {
 com_err ( "rename_principal" , retval , _ ( "while parsing old principal name" ) ) ;
 goto cleanup ;
 }
 retval = kadmin_parse_name ( argv [ argc - 1 ] , & nprinc ) ;
 if ( retval ) {
 com_err ( "rename_principal" , retval , _ ( "while parsing new principal name" ) ) ;
 goto cleanup ;
 }
 retval = krb5_unparse_name ( context , oprinc , & ocanon ) ;
 if ( retval ) {
 com_err ( "rename_principal" , retval , _ ( "while canonicalizing old principal" ) ) ;
 goto cleanup ;
 }
 retval = krb5_unparse_name ( context , nprinc , & ncanon ) ;
 if ( retval ) {
 com_err ( "rename_principal" , retval , _ ( "while canonicalizing new principal" ) ) ;
 goto cleanup ;
 }
 if ( argc == 3 ) {
 printf ( _ ( "Are you sure you want to rename the principal \"%s\" " "to \"%s\"? (yeso): " ) , ocanon , ncanon ) ;
 fgets ( reply , sizeof ( reply ) , stdin ) ;
 if ( strcmp ( "yes\n" , reply ) ) {
 fprintf ( stderr , _ ( "Principal \"%s\" not renamed\n" ) , ocanon ) ;
 goto cleanup ;
 }
 }
 retval = kadm5_rename_principal ( handle , oprinc , nprinc ) ;
 if ( retval ) {
 com_err ( "rename_principal" , retval , _ ( "while renaming principal \"%s\" to \"%s\"" ) , ocanon , ncanon ) ;
 goto cleanup ;
 }
 printf ( _ ( "Principal \"%s\" renamed to \"%s\".\n" ) , ocanon , ncanon ) ;
 printf ( _ ( "Make sure that you have removed the old principal from all ACLs " "before reusing.\n" ) ) ;
 cleanup : krb5_free_principal ( context , nprinc ) ;
 krb5_free_principal ( context , oprinc ) ;
 free ( ncanon ) ;
 free ( ocanon ) ;
 }