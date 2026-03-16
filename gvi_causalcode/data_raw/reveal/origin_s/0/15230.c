static void pk_register_default ( void ) {
 gcry_err_code_t err = 0 ;
 int i ;
 for ( i = 0 ;
 ( ! err ) && pubkey_table [ i ] . pubkey ;
 i ++ ) {

 pubkey_use_dummy ( generate ) ;
 pubkey_use_dummy ( check_secret_key ) ;
 pubkey_use_dummy ( encrypt ) ;
 pubkey_use_dummy ( decrypt ) ;
 pubkey_use_dummy ( sign ) ;
 pubkey_use_dummy ( verify ) ;
 pubkey_use_dummy ( get_nbits ) ;

 }
 if ( err ) BUG ( ) ;
 }