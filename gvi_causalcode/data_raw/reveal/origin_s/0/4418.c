static struct isoent * isoent_find_entry ( struct isoent * rootent , const char * fn ) {




 int l ;
 isoent = rootent ;
 np = NULL ;
 for ( ;
 ;
 ) {
 l = get_path_component ( name , sizeof ( name ) , fn ) ;
 if ( l == 0 ) break ;
 fn += l ;
 if ( fn [ 0 ] == '/' ) fn ++ ;
 np = isoent_find_child ( isoent , name ) ;
 if ( np == NULL ) break ;
 if ( fn [ 0 ] == '\0' ) break ;
 isoent = np ;
 np = NULL ;
 if ( ! isoent -> dir ) break ;
 }
 return ( np ) ;
 }