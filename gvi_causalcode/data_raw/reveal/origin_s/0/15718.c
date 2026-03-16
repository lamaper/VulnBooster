static _Bool have_gcrypt ( void ) {
 static _Bool result = 0 ;
 static _Bool need_init = 1 ;
 if ( ! need_init ) return ( result ) ;
 need_init = 0 ;


 if ( ! gcry_control ( GCRYCTL_INIT_SECMEM , 32768 , 0 ) ) return ( 0 ) ;
 gcry_control ( GCRYCTL_INITIALIZATION_FINISHED , 0 ) ;
 result = 1 ;
 return ( 1 ) ;

