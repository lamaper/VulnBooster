void kadmin_getprincs ( int argc , char * argv [ ] ) {
 krb5_error_code retval ;
 char * expr , * * names ;
 int i , count ;
 expr = NULL ;
 if ( ! ( argc == 1 || ( argc == 2 && ( expr = argv [ 1 ] ) ) ) ) {
 fprintf ( stderr , _ ( "usage: get_principals [expression]\n" ) ) ;
 return ;
 }
 retval = kadm5_get_principals ( handle , expr , & names , & count ) ;
 if ( retval ) {
 com_err ( "get_principals" , retval , _ ( "while retrieving list." ) ) ;
 return ;
 }
 for ( i = 0 ;
 i < count ;
 i ++ ) printf ( "%s\n" , names [ i ] ) ;
 kadm5_free_name_list ( handle , names , count ) ;
 }