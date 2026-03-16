void kadmin_delpol ( int argc , char * argv [ ] ) {
 krb5_error_code retval ;
 char reply [ 5 ] ;
 if ( ! ( argc == 2 || ( argc == 3 && ! strcmp ( "-force" , argv [ 1 ] ) ) ) ) {
 fprintf ( stderr , _ ( "usage: delete_policy [-force] policy\n" ) ) ;
 return ;
 }
 if ( argc == 2 ) {
 printf ( _ ( "Are you sure you want to delete the policy \"%s\"? " "(yeso): " ) , argv [ 1 ] ) ;
 fgets ( reply , sizeof ( reply ) , stdin ) ;
 if ( strcmp ( "yes\n" , reply ) ) {
 fprintf ( stderr , _ ( "Policy \"%s\" not deleted.\n" ) , argv [ 1 ] ) ;
 return ;
 }
 }
 retval = kadm5_delete_policy ( handle , argv [ argc - 1 ] ) ;
 if ( retval ) {
 com_err ( "delete_policy:" , retval , _ ( "while deleting policy \"%s\"" ) , argv [ argc - 1 ] ) ;
 }
 }