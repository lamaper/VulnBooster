static void check_matching ( void ) {
 gpg_error_t err ;
 gcry_sexp_t key ;
 const char * name ;
 unsigned int nbits ;
 err = gcry_sexp_new ( & key , sample_key_1 , 0 , 1 ) ;
 if ( err ) die ( "parsing s-expression string failed: %s\n" , gpg_strerror ( err ) ) ;
 name = gcry_pk_get_curve ( key , 0 , & nbits ) ;
 if ( ! name ) fail ( "curve name not found for sample_key_1\n" ) ;
 else if ( strcmp ( name , sample_key_1_curve ) ) fail ( "expected curve name %s but got %s for sample_key_1\n" , sample_key_1_curve , name ) ;
 else if ( nbits != sample_key_1_nbits ) fail ( "expected curve size %u but got %u for sample_key_1\n" , sample_key_1_nbits , nbits ) ;
 gcry_sexp_release ( key ) ;
 err = gcry_sexp_new ( & key , sample_key_2 , 0 , 1 ) ;
 if ( err ) die ( "parsing s-expression string failed: %s\n" , gpg_strerror ( err ) ) ;
 name = gcry_pk_get_curve ( key , 0 , & nbits ) ;
 if ( ! name ) fail ( "curve name not found for sample_key_2\n" ) ;
 else if ( strcmp ( name , sample_key_2_curve ) ) fail ( "expected curve name %s but got %s for sample_key_2\n" , sample_key_2_curve , name ) ;
 else if ( nbits != sample_key_2_nbits ) fail ( "expected curve size %u but got %u for sample_key_2\n" , sample_key_2_nbits , nbits ) ;
 gcry_sexp_release ( key ) ;
 }