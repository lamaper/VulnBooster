static void list_curves ( void ) {
 int idx ;
 const char * name ;
 unsigned int nbits ;
 for ( idx = 0 ;
 ( name = gcry_pk_get_curve ( NULL , idx , & nbits ) ) ;
 idx ++ ) {
 if ( verbose ) printf ( "%s - %u bits\n" , name , nbits ) ;
 }
 if ( idx != N_CURVES ) fail ( "expected %d curves but got %d\n" , N_CURVES , idx ) ;
 if ( gcry_pk_get_curve ( NULL , - 1 , NULL ) ) fail ( "curve iteration failed\n" ) ;
 }