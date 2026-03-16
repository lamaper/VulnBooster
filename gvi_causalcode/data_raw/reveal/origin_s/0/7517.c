int main ( int argc , char * * argv ) {
 int debug = 0 ;
 if ( argc > 1 && ! strcmp ( argv [ 1 ] , "--verbose" ) ) verbose = 1 ;
 else if ( argc > 1 && ! strcmp ( argv [ 1 ] , "--debug" ) ) verbose = debug = 1 ;
 if ( ! gcry_check_version ( GCRYPT_VERSION ) ) die ( "version mismatch\n" ) ;
 gcry_control ( GCRYCTL_DISABLE_SECMEM , 0 ) ;
 gcry_control ( GCRYCTL_INITIALIZATION_FINISHED , 0 ) ;
 if ( debug ) gcry_control ( GCRYCTL_SET_DEBUG_FLAGS , 1u , 0 ) ;
 list_curves ( ) ;
 check_matching ( ) ;
 check_get_params ( ) ;
 return error_count ? 1 : 0 ;
 }