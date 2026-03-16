static void check_get_params ( void ) {
 gcry_sexp_t param ;
 const char * name ;
 param = gcry_pk_get_param ( GCRY_PK_ECDSA , sample_key_1_curve ) ;
 if ( ! param ) fail ( "error gerring parameters for `%s'\n" , sample_key_1_curve ) ;
 name = gcry_pk_get_curve ( param , 0 , NULL ) ;
 if ( ! name ) fail ( "get_param: curve name not found for sample_key_1\n" ) ;
 else if ( strcmp ( name , sample_key_1_curve ) ) fail ( "get_param: expected curve name %s but got %s for sample_key_1\n" , sample_key_1_curve , name ) ;
 gcry_sexp_release ( param ) ;
 param = gcry_pk_get_param ( GCRY_PK_ECDSA , sample_key_2_curve ) ;
 if ( ! param ) fail ( "error gerring parameters for `%s'\n" , sample_key_2_curve ) ;
 name = gcry_pk_get_curve ( param , 0 , NULL ) ;
 if ( ! name ) fail ( "get_param: curve name not found for sample_key_2\n" ) ;
 else if ( strcmp ( name , sample_key_2_curve ) ) fail ( "get_param: expected curve name %s but got %s for sample_key_2\n" , sample_key_2_curve , name ) ;
 gcry_sexp_release ( param ) ;
 }